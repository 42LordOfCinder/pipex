/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:29:41 by gmassoni          #+#    #+#             */
/*   Updated: 2024/01/31 19:41:36 by gmassoni         ###   ########.fr       */
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

char	*ft_get_cmd(char *str)
{
	int		i;

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
	while (env[i])
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

char	*ft_check_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (access(tmp, X_OK) != -1)
			return (tmp);
		if (access(tmp, F_OK) != -1)
		{
			free(tmp);
			return ("2");
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

char	**ft_get_cmds_paths(int argc, char **argv, char **env)
{
	char	**paths;
	char	*cmd;
	int		i;
	char	*res;

	paths = ft_get_paths(env);
	i = 1;
	while (i++ < argc - 2)
	{
		cmd = ft_get_cmd(argv[i]);
		res = ft_check_cmd(paths, cmd);
		if (res == NULL)
		{
			ft_putstr_fd("\033[0;31mPipex: Command not found: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("\033[0m\n", 2);
		}
		else if (ft_strncmp(res, "2", 1) == 0)
		{
			ft_putstr_fd("\033[0;31mPipex: Permission denied: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("\033[0m\n", 2);
		}
	}
	ft_free_split(paths);
}
