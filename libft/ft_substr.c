/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gauthier.massoni@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:21:43 by gmassoni          #+#    #+#             */
/*   Updated: 2023/11/06 19:15:36 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	i = start;
	if (start >= s_len)
	{
		substr = malloc(sizeof(char));
		i++;
	}
	else if (start < s_len && start + len <= s_len)
		substr = malloc((len + 1) * sizeof(char));
	else
		substr = malloc(((s_len - start + 1)) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	if (start < s_len)
		while (s[i++] && i - 1 < start + len)
			substr[i - start - 1] = s[i - 1];
	substr[i - start - 1] = 0;
	return (substr);
}
