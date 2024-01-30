/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:29:41 by gmassoni          #+#    #+#             */
/*   Updated: 2024/01/30 18:35:41 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_files(int argc, char **argv, int *infile_fd, int *outfile_fd)
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
	fd2 = open(argv[argc - 1], O_CREAT, 00600 | 00040 | 00004);
	if (fd2 == -1)
	{
		ft_putstr_fd("\033[0;31mPipex: ", 2);
		perror(argv[argc - 1]);
		ft_putstr_fd("\033[0m", 2);
		return (0);
	}
	*infile_fd = fd1;
	*outfile_fd = fd2;
	return (1);
}

char	*ft_get_cmd_path(char *str)
{
	int		i;
	char	*path;

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
	path = ft_strjoin("/bin/", str);
	return (path);
}

void	ft_check_cmds(int argc, char **argv)
{
	int		i;
	char	*path;

	i = 2;
	while (i < argc - 1)
	{
		path = ft_get_cmd_path(argv[i]);
		if (access(path, X_OK) == -1)
		{
			ft_putstr_fd("\033[0;31mPipex: Command not found: ", 2);
			ft_putstr_fd(path + 5, 2);
			ft_putstr_fd("\033[0m\n", 2);
		}
		free(path);
		i++;
	}
}
