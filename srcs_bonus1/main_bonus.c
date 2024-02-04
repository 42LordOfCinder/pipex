/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:04:01 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/03 05:45:59 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_file(char *path, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(path, O_RDONLY);
	else
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Pipex: ", 2);
		perror(path);
	}
	return (fd);
}

void	ft_close_fds(int fds[2])
{
	if (fds[0] > 2)
		close(fds[0]);
	if (fds[1] > 2)
		close(fds[1]);
}

char	*ft_get_cmd_without_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			str[i] = 0;
			break ;
		}
		i++;
	}
	return (str);
}

char	**ft_get_paths(char **env)
{
	int		i;
	int		j;
	char	**paths;
	char	*tmp;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5, ':');
			j = 0;
			while (paths[j])
			{
				tmp = ft_strjoin(paths[j], "/");
				free(paths[j]);
				paths[j] = tmp;
				j++;
			}
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*ft_handle_no_paths(char *cmd)
{
	if (access(cmd, X_OK) != -1)
		return (cmd);
	if (access(cmd, F_OK) != -1)
		return ("/ / /");
	return (NULL);
}

char	*ft_check_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_handle_no_paths(cmd);
	if (tmp != NULL)
		return (tmp);
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (access(tmp, X_OK) != -1)
		{
			ft_free_tab(paths);
			return (tmp);
		}
		if (access(tmp, F_OK) != -1)
		{
			ft_free_tab(paths);
			free(tmp);
			return ("/ / /");
		}
		free(tmp);
		i++; 
	}
	if (paths)
		ft_free_tab(paths);
	return (NULL);
}

void	ft_execute_cmd(char *cmd, char **env, char **args)
{
	char	*res;

	res = ft_check_cmd(ft_get_paths(env), cmd);
	if (res == NULL)
	{
		ft_putstr_fd("Pipex: Command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		ft_free_tab(args);
		exit(1);
	}
	else if (ft_strncmp(res, "/ / /", 5) == 0)
	{
		ft_putstr_fd("Pipex: Permission denied: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		ft_free_tab(args);
		exit(1);
	}
	else
		execve(res, args, env);
}

void	ft_pipe_and_fork(char *cmd, char **env, char **args, int last)
{
	pid_t	child_pid;
	int		pipe_fds[2];

	pipe(pipe_fds);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(pipe_fds[0]);
		if (last > 0)
			dup2(last, 1);
		else
			dup2(pipe_fds[1], 1);
		ft_execute_cmd(ft_get_cmd_without_args(cmd), env, args);
	}
	else
	{
		dup2(pipe_fds[0], 0);
		ft_close_fds(pipe_fds);
	}
}

void	ft_wait_children(int i)
{
	int	j;

	j = 0;
	while (j < i - 2)
	{
		wait(NULL);
		ft_printf("wait(NULL)\n");
		j++;
	}
}

void	ft_pipex(int argc, char **argv, char **env)
{
	int		fds[2];
	int		i;
	char	**args;

	fds[0] = ft_open_file(argv[1], 0);
	fds[1] = ft_open_file(argv[argc - 1], 1);
	if (fds[0] == -1 || fds[1] == -1)
	{
		ft_close_fds(fds);
		exit(1);
	}
	dup2(fds[0], 0);
	i = 2;
	while (i < argc - 1)
	{
		args = ft_split(argv[i], ' ');
		if (i == argc - 2)
			ft_pipe_and_fork(argv[i], env, args, fds[1]);
		else
			ft_pipe_and_fork(argv[i], env, args, -1);
		ft_free_tab(args);
		i++;
	}
	ft_close_fds(fds);
	ft_wait_children(i);
}

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		ft_putstr_fd("Pipex: Too few arguments\n", 2);
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		ft_printf("heredoc\n");
	else
		ft_pipex(argc, argv, env);
	return (0);
}
