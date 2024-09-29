/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dplackov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:32:00 by dplackov          #+#    #+#             */
/*   Updated: 2024/09/26 11:32:01 by dplackov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_utils(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc_utils(size_t nmemb, size_t size)
{
	size_t			prod;
	unsigned char	*out;
	size_t			i;

	prod = nmemb * size;
	if (nmemb && prod / nmemb != size)
		return (NULL);
	out = malloc(prod);
	if (!out)
		return (NULL);
	i = 0;
	while (i < prod)
	{
		((unsigned char *)out)[i] = 0;
		i++;
	}
	return ((void *)out);
}

char	*ft_substr_utils(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen_utils(s);
	if (len > slen - start)
		len = slen - start;
	out = (char *)ft_calloc_utils(len + 1, 1);
	if (!out)
		return (NULL);
	i = 0;
	while (start + i <= len)
	{
		out[i] = s[start + i];
		i++;
	}
	return (out);
}

char	*ft_strchr_utils(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (NULL);
	return ((char *)(s + i));
}
