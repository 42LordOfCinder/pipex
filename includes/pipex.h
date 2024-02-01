/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:06:27 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/01 02:31:40 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

int		main(int argc, char **argv, char **env);

// Parsing
int		ft_open_files(int argc, char **argv, int *fds);
char	*ft_get_cmd(char *str);
char	**ft_get_paths(char **env);
char	*ft_check_cmd(char **paths, char *cmd);
int		ft_handle_path_errors(char *res, char *cmd);
t_list	*ft_get_cmds_paths(int argc, char **argv, char **env);

#endif
