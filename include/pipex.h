/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:06:27 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/02 04:39:21 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

int		main(int argc, char **argv, char **env);
void	ft_open_files(char *path1, char *path2, int fd[2]);
void	ft_execute_cmd(char *cmd, char **env);
void	ft_do_first_cmd(char **argv, int pipe_fds[2], char **env, int fds[2]);
void	ft_do_second_cmd(char **argv, int pipe_fds[2], char **env, int fds[2]);
char	*ft_get_cmd_without_args(char *str);
char	**ft_get_paths(char **env);
char	*ft_handle_no_paths(char *cmd);
char	*ft_check_cmd(char **paths, char *cmd_alone);
#endif
