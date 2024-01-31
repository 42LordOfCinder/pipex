/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:07:05 by gmassoni          #+#    #+#             */
/*   Updated: 2024/01/31 19:42:53 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute_cmds(int argc, char **argv, int *fds, char **env)
{
	//char	*cmd[] = {"ls", "-l", NULL};

	//execve("/bin/ls", cmd, env);
	(void) argc;
	(void) argv;
	(void) fds;
	(void) env;
}

int	main(int argc, char **argv, char **env)
{
	int		*fds;
	char	**cmds_paths;

	if (argc < 5)
	{
		ft_putstr_fd("\033[0;31mPipex: Too few arguments\033[0m\n", 2);
		return (-1);
	}
	fds = malloc(sizeof(int) * 2);
	if (!ft_open_files(argc, argv, fds))
		return (-1);
	cmds_paths = ft_get_cmds_paths(argc, argv, env);
	ft_execute_cmds(argc, argv, fds, env);
	close(fds[0]);
	close (fds[1]);
	free(fds);
	return (0);
}
