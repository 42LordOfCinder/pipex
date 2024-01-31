/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:07:05 by gmassoni          #+#    #+#             */
/*   Updated: 2024/01/31 18:57:41 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute_cmds(int argc, char **argv, int *fds, char **env)
{
	(void) env;
	(void) argc;
	(void) argv;
	(void) fds;
}

int	main(int argc, char **argv, char **env)
{
	int	*fds;

	if (argc < 5)
	{
		ft_putstr_fd("\033[0;31mPipex: Too few arguments\033[0m\n", 2);
		return (-1);
	}
	fds = malloc(sizeof(int) * 2);
	if (!ft_open_files(argc, argv, fds))
		return (-1);
	ft_check_cmds(argc, argv, env);
	ft_execute_cmds(argc, argv, fds, env);
	close(fds[0]);
	close (fds[1]);
	free(fds);
	return (0);
}
