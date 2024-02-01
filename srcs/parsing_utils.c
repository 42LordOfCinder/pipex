/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:29:41 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/01 02:58:38 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (access(tmp, X_OK) != -1 || access(cmd, X_OK) != -1)
		{
			ft_free_split(paths);
			return (tmp);
		}
		if (access(tmp, F_OK) != -1 || access(cmd, F_OK) != -1)
		{
			ft_free_split(paths);
			free(tmp);
			return ("/ / /");
		}
		free(tmp);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

int	ft_handle_path_errors(char *res, char *cmd)
{
	if (res == NULL)
	{
		ft_putstr_fd("\033[0;31mPipex: Command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\033[0m\n", 2);
		return (0);
	}
	else if (ft_strncmp(res, "/ / /", 5) == 0)
	{
		ft_putstr_fd("\033[0;31mPipex: Permission denied: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\033[0m\n", 2);
		return (0);
	}
	return (1);
}

t_list	*ft_get_cmds_paths(int argc, char **argv, char **env)
{
	char	*cmd;
	int		i;
	char	*res;
	t_list	*cmds;

	i = 1;
	cmds = NULL;
	while (i++ < argc - 2)
	{
		cmd = ft_get_cmd(ft_strdup(argv[i]));
		res = ft_check_cmd(ft_get_paths(env), cmd);
		if (ft_handle_path_errors(res, cmd))
			ft_lstadd_back(&cmds, ft_lstnew(res));
		free(cmd);
	}
	return (cmds);
}
