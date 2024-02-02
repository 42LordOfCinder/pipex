/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 03:27:41 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/02 05:55:18 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*ft_handle_no_paths(char *cmd)
{
	if (access(cmd, X_OK) != -1)
		return (cmd);
	if (access(cmd, F_OK) != -1)
		return ("/ / /");
	return (NULL);
}

char	*ft_check_cmd(char **paths, char *cmd_alone)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_handle_no_paths(cmd_alone);
	if (tmp != NULL)
		return (tmp);
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd_alone);
		if (access(tmp, X_OK) == 0)
		{
			ft_free_tab(paths);
			return (tmp);
		}
		if (access(tmp, F_OK) == 0)
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
