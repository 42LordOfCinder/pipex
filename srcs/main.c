/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:07:05 by gmassoni          #+#    #+#             */
/*   Updated: 2024/01/30 19:02:55 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute_cmds(int argc, char **argv, int infile_fd, int outfile_fd);
{
	(void) argc;
	(void) argv;
	(void) infile_fd;
	(void) outfile_fd;
}

int	main(int argc, char **argv)
{
	int	infile_fd;
	int	outfile_fd;

	if (argc < 5)
	{
		ft_putstr_fd("\033[0;31mPipex: Too few arguments\033[0m\n", 2);
		return (-1);
	}
	if (!ft_open_files(argc, argv, &infile_fd, &outfile_fd))
		return (-1);
	ft_check_cmds(argc, argv);
	ft_execute_cmds(argc, argv, infile_fd, outfile_fd);
	close(infile_fd);
	close (outfile_fd);
	return (0);
}
