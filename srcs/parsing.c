/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:11:05 by gmassoni          #+#    #+#             */
/*   Updated: 2024/02/25 19:28:22 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Just like ft_substr but return NULL when len is 0
char	*ft_substr2(char *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;

	if (len == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (start + i < ft_strlen(s) && i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_parse_quotes(char *cmd, int last, int j)
{
	char	*s;
	int		i;
	int		ob[2];

	s = ft_substr2(cmd, last, j - last);
	if (!s)
		return (NULL);
	ob[0] = -1;
	ob[1] = -1;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '"' && ob[1] == -1) || (s[i] == '\'' && ob[0] == -1))
		{
			if (s[i] == '"')
				ob[0] = -ob[0];
			else if (s[i] == '\'')
				ob[1] = -ob[1];
			s = ft_remove_char(s, i);
		}
		else
			i++;
	}
	return (s);
}

int	ft_is_in_quotes(char *cmd, int j)
{
	int	i;
	int	open_bools[2];

	i = 0;
	open_bools[0] = -1;
	open_bools[1] = -1;
	while (cmd[i])
	{
		if (cmd[i] == '"' && open_bools[1] == -1)
			open_bools[0] = -open_bools[0];
		if (cmd[i] == '\'' && open_bools[0] == -1)
			open_bools[1] = -open_bools[1];
		if (i == j)
		{
			if (open_bools[0] == 1 || open_bools[1] == 1)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

char	**ft_split_by_quotes(char *cmd)
{
	int		i;
	char	**res;
	int		last;

	res = NULL;
	i = 0;
	last = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' && !ft_is_in_quotes(cmd, i))
		{
			res = ft_add_element_tab(res, ft_parse_quotes(cmd, last, i));
			last = i + 1;
		}
		else if (!cmd[i + 1])
			res = ft_add_element_tab(res, ft_parse_quotes(cmd, last, i + 1));
		i++;
	}
	return (res);
}

char	**ft_parse_cmd(char *cmd, char *str_to_free)
{
	char	**res;
	int		quotes;

	if (!cmd || !*cmd)
		return (NULL);
	quotes = ft_is_in_quotes(cmd, ft_strlen(cmd) - 1);
	if (quotes == 1)
	{
		ft_putstr_fd("Pipex: Unclosed quotes\n", 2);
		free(str_to_free);
		free(cmd);
		exit(1);
	}
	res = ft_split_by_quotes(cmd);
	return (res);
}
