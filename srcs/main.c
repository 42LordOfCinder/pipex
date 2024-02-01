/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:07:05 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/01 04:44:15 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_files(int argc, char **argv, int *fds)
{
	int	fd1;
	int	fd2;

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
	{
		ft_putstr_fd("\033[0;31mPipex: ", 2);
		perror(argv[1]);
		ft_putstr_fd("\033[0m", 2);
		return (0);
	}
	fd2 = open(argv[argc - 1], O_CREAT, 0644);
	if (fd2 == -1)
	{
		ft_putstr_fd("\033[0;31mPipex: ", 2);
		perror(argv[argc - 1]);
		ft_putstr_fd("\033[0m", 2);
		return (0);
	}
	fds[0] = fd1;
	fds[1] = fd2;
	return (1);
}

void	ft_execute_cmd(char *path, char *cmd, char **env)
{
	pid_t	child_pid;
	char	**args;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("\033[0;31mPipex: ");
		ft_putstr_fd("\033[0m", 2);
		return ;
	}
	args = ft_split(cmd, ' ');
	if (child_pid == 0)
		execve(path, args, env);
	else
		ft_free_split(args);
}

void	ft_handle_cmds(t_list *cmds, int *fds, char **argv, char **env)
{
	int	i;
	int	j;
	int	pipe_fds[2];

	i = 2;
	while (cmds)
	{
		pipe(pipe_fds);
		ft_execute_cmd(cmds->content, argv[i], env);
		cmds = cmds->next;
		i++;
	}
	j = 0;
	while (j < i - 2)
	{
		wait(NULL);
		j++;
	}
	(void) fds;
}

int	main(int argc, char **argv, char **env)
{
	int		*fds;
	t_list	*cmds_paths;

	if (argc < 5)
	{
		ft_putstr_fd("\033[0;31mPipex: Too few arguments\033[0m\n", 2);
		return (-1);
	}
	fds = malloc(sizeof(int) * 2);
	if (fds == NULL)
		return (-1);
	if (!ft_open_files(argc, argv, fds))
	{
		free(fds);
		return (-1);
	}
	cmds_paths = ft_get_cmds_paths(argc, argv, env);
	ft_handle_cmds(cmds_paths, fds, argv, env);
	ft_lstfree(&cmds_paths);
	close(fds[0]);
	close(fds[1]);
	free(fds);
	return (0);
}
