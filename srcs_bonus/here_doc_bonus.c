/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:30:58 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/05 19:34:09 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_read_here_doc(char *limiter, int fd)
{
	char	*str;
	char	*buffer;
	char	*tmp;

	close(fd);
	buffer = NULL;
	while (1) // write pipe here_doc >
	{
		str = get_next_line(0);
		ft_putstr_fd(buffer, 2);
		if (str == NULL && buffer == NULL)
		{
			ft_putstr_fd("warning machin\n", 2);
			exit(1);
		}
		tmp = ft_strjoin(buffer, str);
		if (str)
			free(str);
		if (buffer)
			free(buffer);
		buffer = tmp;
		if (ft_strchr(buffer, '\n') != NULL)
		{
			if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0)
			{
				free(buffer);
				break ;
			}
			else
			{
				ft_putstr_fd(str, 1);
				free(buffer);
				buffer = NULL;
			}
		}
	}
	exit(0);
}

void	ft_handle_here_doc(int fds[2], char *outfile, char *limiter)
{
	int		pipe_fds[2];
	pid_t	child_pid;

	pipe(pipe_fds);
	close(pipe_fds[1]);
	child_pid = fork();
	if (child_pid == 0)
		ft_read_here_doc(limiter, pipe_fds[0]);
	fds[0] = pipe_fds[0];
	fds[1] = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fds[1] == -1)
	{
		if (fds[0] > -1)
			close(fds[0]);
		ft_putstr_fd("Pipex: ", 2);
		perror(outfile);
		exit(1);
	}
}
