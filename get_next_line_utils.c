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

#include <stdlib.h>
#include <sys/types.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
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

int	ft_strchr(const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len && s[i] != c)
		i++;
	if (i == len)
		return (-1);
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*out;
	size_t	i;

	len = ft_strlen(s) + 1;
	out = (char *)ft_calloc(len, 1);
	if (!out)
		return (NULL);
	i = 0;
	while (s[i])
	{
		out[i] = s[i];
		i++;
	}
	return (out);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;

	if (!s)
		return (NULL);
	out = (char *)ft_calloc(len + 2, 1);
	if (!out)
		return (NULL);
	s += start;
	i = 0;
	while (i < len + 1)
	{
		out[i] = s[i];
		i++;
	}
	return (out);
}
