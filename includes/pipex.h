/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:06:27 by gmassoni          #+#    #+#             */
/*   Updated: 2024/01/30 18:29:27 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>

int		main(int argc, char **argv);

// Parsing
int		ft_open_files(int argc, char **argv, int *infile_fd, int *outfile_fd);
char	*ft_get_cmd_path(char *str);
void	ft_check_cmds(int argc, char **argv);

#endif
