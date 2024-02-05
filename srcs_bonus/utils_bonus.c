/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 03:10:17 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/05 03:23:03 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
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

char	*ft_handle_no_paths(char *cmd, char **paths)
{
	if (access(cmd, X_OK) != -1)
	{
		if (paths)
			ft_free_tab(paths);
		return (cmd);
	}
	if (access(cmd, F_OK) != -1)
	{
		if (paths)
			ft_free_tab(paths);
		return ("/ / /");
	}
	return (NULL);
}

char	*ft_check_cmd(char **paths, char *cmd_alone)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_handle_no_paths(cmd_alone, paths);
	if (tmp != NULL)
		return (tmp);
	while (paths && paths[++i])
	{
		tmp = ft_strjoin(paths[i], cmd_alone);
		if (access(tmp, X_OK) == 0)
			ft_free_tab(paths);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		if (access(tmp, F_OK) == 0)
		{
			ft_free_tab(paths);
			free(tmp);
			return ("/ / /");
		}
		free(tmp);
	}
	if (paths)
		ft_free_tab(paths);
	return (NULL);
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
