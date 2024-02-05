/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:50:50 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/05 17:57:48 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open_files(char *path1, char *path2, int fds[2])
{
	fds[0] = open(path1, O_RDONLY);
	if (fds[0] == -1)
	{
		ft_putstr_fd("Pipex: ", 2);
		perror(path1);
	}
	fds[1] = open(path2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fds[1] == -1)
	{
		if (fds[0] > -1)
			close(fds[0]);
		ft_putstr_fd("Pipex: ", 2);
		perror(path2);
		exit(1);
	}
}

void	ft_execute_cmd(char *cmd, char **env)
{
	char	*res;
	char	*cmd_cpy;
	char	**cmd_parsed;

	cmd_cpy = ft_strdup(cmd);
	res = ft_check_cmd(ft_get_paths(env), ft_get_cmd_without_args(cmd));
	if (res == NULL || ft_strncmp(res, "/ / /", 5) == 0)
	{
		if (res == NULL)
			ft_putstr_fd("Pipex: Command not found: ", 2);
		else
			ft_putstr_fd("Pipex: Permission denied: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		free(cmd_cpy);
		exit(1);
	}
	cmd_parsed = ft_parse_cmd(cmd_cpy, res);
	execve(res, cmd_parsed, env);
	ft_putstr_fd("Pipex: ", 2);
	perror(cmd);
	free(cmd_cpy);
	ft_free_tab(cmd_parsed);
	exit(1);
}

void	ft_do_first_cmd(char **argv, int pipe_fds[2], char **env, int fds[2])
{
	close(pipe_fds[0]);
	close(fds[1]);
	dup2(pipe_fds[1], 1);
	close(pipe_fds[1]);
	dup2(fds[0], 0);
	if (fds[0] != -1)
	{
		close(fds[0]);
		ft_execute_cmd(argv[2], env);
	}
	else
		ft_execute_cmd("/bin/true", env);
}

pid_t	ft_do_second_cmd(char **argv, int pipe_fds[2], char **env, int fds[2])
{
	pid_t	child_pid;
	int		pipe2_fds[2];

	if (fds[0] != -1)
		close(fds[0]);
	dup2(pipe_fds[0], 0);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	pipe(pipe2_fds);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(pipe2_fds[0]);
		dup2(fds[1], 1);
		close(pipe2_fds[1]);
		close(fds[1]);
		ft_execute_cmd(argv[3], env);
	}
	close(fds[1]);
	dup2(pipe2_fds[0], 0);
	close(pipe2_fds[0]);
	close(pipe2_fds[1]);
	return (child_pid);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	child_pid;
	pid_t	child_pid2;
	int		pipe_fds[2];
	int		fds[2];
	int		status;

	child_pid2 = 0;
	if (argc != 5)
	{
		ft_putstr_fd("Pipex: Expected 4 arguments: file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	ft_open_files(argv[1], argv[4], fds);
	pipe(pipe_fds);
	child_pid = fork();
	if (child_pid == 0)
		ft_do_first_cmd(argv, pipe_fds, env, fds);
	else
		child_pid2 = ft_do_second_cmd(argv, pipe_fds, env, fds);
	waitpid(child_pid, NULL, 0);
	waitpid(child_pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
