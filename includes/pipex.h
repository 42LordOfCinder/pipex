/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:06:27 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/07 02:22:42 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
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
pid_t	ft_do_second_cmd(char **argv, int pipe_fds[2], char **env, int fds[2]);
char	*ft_get_cmd_without_args(char *str);
char	**ft_get_paths(char **env);
char	*ft_handle_no_paths(char *cmd, char **paths);
char	*ft_check_cmd(char **paths, char *cmd_alone);
char	*ft_substr2(char *s, unsigned int start, size_t len);
char	*ft_parse_quotes(char *cmd, int last, int j);
int		ft_is_in_quotes(char *cmd, int j);
char	**ft_split_by_quotes(char *cmd);
char	**ft_parse_cmd(char *cmd, char *str_to_free);
#endif
