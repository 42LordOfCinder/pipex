/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:06:27 by gmassoni          #+#    #+#             */
/*   Updated: 2024/01/31 18:55:45 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>

int		main(int argc, char **argv, char **env);

// Parsing
int		ft_open_files(int argc, char **argv, int *fds);
char	*ft_get_cmd(char *str);
char	**ft_get_paths(char **env);
int		ft_check_cmd(char **paths, char *cmd);
void	ft_check_cmds(int argc, char **argv, char **env);

#endif
