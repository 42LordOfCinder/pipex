/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:10:14 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/15 04:17:13 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_open_files(char *path1, char *path2, int fds[2], int mode)
{
	if (mode == 1)
		fds[0] = open(path1, O_RDONLY);
	else
		fds[0] = open(path1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fds[0] == -1)
	{
		ft_putstr_fd("Pipex: ", 2);
		perror(path1);
	}
	if (mode == 1)
		fds[1] = open(path2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fds[1] = open(path2, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fds[1] == -1)
	{
		if (fds[0] > -1)
			close(fds[0]);
		ft_putstr_fd("Pipex: ", 2);
		perror(path2);
		exit(1);
	}
}

void	ft_close_fds(int fds[2])
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
}

int	ft_pipe_and_fork(char *cmd, char **env, int position, int fds[2])
{
	pid_t	child_pid;
	int		pipe_fds[2];

	pipe(pipe_fds);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(pipe_fds[0]);
		if (position == 1)
			dup2(fds[1], 1);
		else
			dup2(pipe_fds[1], 1);
		close(pipe_fds[1]);
		close(fds[1]);
		if (position == 0 && fds[0] == -1)
			ft_execute_cmd("/bin/false", env);
		if (position == 0)
			dup2(fds[0], 0);
		if (fds[0] != -1)
			close(fds[0]);
		ft_execute_cmd(cmd, env);
	}
	dup2(pipe_fds[0], 0);
	ft_close_fds(pipe_fds);
	return (child_pid);
}

int	ft_pipex(int argc, char **argv, char **env, int fds[2])
{
	int	i;
	int	pids[262144];
	int	status;

	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		i++;
	while (i < argc - 1)
	{
		if (i == argc - 2)
			pids[i - 2] = ft_pipe_and_fork(argv[i], env, 1, fds);
		else if (i == 2 || (ft_strncmp(argv[1], "here_doc", 9) == 0 && i == 3))
			pids[i - 2] = ft_pipe_and_fork(argv[i], env, 0, fds);
		else
			pids[i - 2] = ft_pipe_and_fork(argv[i], env, -1, fds);
		i++;
	}
	i = -1;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		i++;
	while (++i < argc - 3)
		waitpid(pids[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int	exit_code;
	int	fds[2];

	if (argc < 5)
	{
		ft_putstr_fd("Pipex: Too few arguments\n", 2);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
		{
			ft_putstr_fd("Pipex: here_doc: Too few arguments\n", 2);
			return (1);
		}
		ft_handle_here_doc(fds, argv[argc - 1], argv[2]);
	}
	else
		ft_open_files(argv[1], argv[argc - 1], fds, 1);
	exit_code = ft_pipex(argc, argv, env, fds);
	ft_close_fds(fds);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		unlink(".wowthisfileissotemporaryomgimshockedfr");
	return (exit_code);
}
