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
	while (i < len)
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

char	*ft_strjoin_free(char **s1, char **s2)
{
	char	*out;
	int		s1_len;
	int		total_len;
	size_t	i;

	if (!*s1 || !*s2)
		return (NULL);
	s1_len = ft_strlen_utils(*s1);
	total_len = s1_len + ft_strlen_utils(*s2) + 1;
	out = (char *)ft_calloc_utils(total_len, 1);
	if (!out)
	{
		free((void *)*s1);
		return (NULL);
	}
	i = -1;
	while ((*s1)[++i])
		out[i] = (*s1)[i];
	i = -1;
	while ((*s2)[++i])
		out[s1_len + i] = (*s2)[i];
	free((void *)(*s1));
	return (out);
}
