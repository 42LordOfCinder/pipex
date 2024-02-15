/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:30:58 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/15 04:42:46 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_cmp(char *buffer, char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (buffer[i] != limiter[i])
			return (0);
		i++;
	}
	if (buffer[i] == '\n')
		return (1);
	return (0);
}

char	*ft_append_input(char *buffer, char *limiter)
{
	char	*str;
	char	*tmp;

	str = get_next_line(0, 0);
	if (str == NULL && buffer == NULL)
	{
		ft_putstr_fd("\nPipex: Warning: here-document delimited", 2);
		ft_putstr_fd(" by end-of-file (wanted `", 2);
		ft_putstr_fd(limiter, 2);
		ft_putstr_fd("')\n", 2);
		return (NULL);
	}
	tmp = ft_strjoin(buffer, str);
	if (str)
		free(str);
	if (buffer)
		free(buffer);
	return (tmp);
}

int	ft_read_here_doc(char *limiter, int fd)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		if (!buffer)
			ft_putstr_fd("> ", 1);
		buffer = ft_append_input(buffer, limiter);
		if (!buffer)
			return (0);
		if (buffer[ft_strlen(buffer) - 1] == '\n')
		{
			if (ft_cmp(buffer, limiter))
			{
				get_next_line(0, 1);
				free(buffer);
				return (1);
			}
			write(fd, buffer, ft_strlen(buffer));
			free(buffer);
			buffer = NULL;
		}
	}
}

void	ft_handle_here_doc(int fds[2], char *outfile, char *limiter)
{
	char	*infile;

	infile = ".wowthisfileissotemporaryomgimshockedfr";
	ft_open_files(infile, outfile, fds, 2);
	if (!ft_read_here_doc(limiter, fds[0]))
	{
		close(fds[0]);
		unlink(infile);
		fds[0] = -1;
	}
	else
	{
		close(fds[0]);
		fds[0] = open(infile, O_RDONLY);
		if (fds[0] == -1)
		{
			ft_putstr_fd("Pipex: ", 2);
			perror(infile);
		}
	}
}
