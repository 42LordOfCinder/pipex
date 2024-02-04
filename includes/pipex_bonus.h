/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:06:27 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/04 18:11:57 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

int		main(int argc, char **argv, char **env);
char	*ft_substr2(char *s, unsigned int start, size_t len);
char	*ft_parse_quotes(char *cmd, int last, int j);
int		ft_is_in_quotes(char *cmd, int j);
char	**ft_split_by_quotes(char *cmd);
char	**ft_parse_cmd(char *cmd, char *str_to_free);
#endif
