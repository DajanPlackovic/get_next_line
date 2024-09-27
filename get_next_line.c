/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dplackov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:31:41 by dplackov          #+#    #+#             */
/*   Updated: 2024/09/26 11:31:43 by dplackov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strchr(const char *s, char c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	int		s1_len;
	int		total_len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	total_len = s1_len + ft_strlen(s2) + 1;
	out = (char *)ft_calloc(total_len, 1);
	if (!out)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	while (s2[i])
	{
		out[s1_len + i] = s2[i];
		i++;
	}
	free((void *)s1);
	return (out);
}

char	*extract_line(int fd, char **text, char **buff)
{
	ssize_t	bread;
	int		pos;
	char	*out;

	bread = 1;
	while (bread > 0)
	{
		pos = ft_strchr(*text, '\n');
		if (pos + 1)
		{
			out = ft_substr(*text, 0, pos);
			*buff = ft_substr(*text, pos + 1, ft_strlen(*text) - pos);
			free(*text);
			return (out);
		}
		else
		{
			bread = read(fd, *buff, BUFFER_SIZE);
			*text = ft_strjoin(*text, *buff);
		}
	}
	return (NULL);
}

char	*handle_line(int fd, char *text, char **buff)
{
	char	*out;

	out = extract_line(fd, &text, buff);
	if (out)
		return (out);
	if (*buff)
	{
		free(*buff);
		*buff = NULL;
	}
	if (text[0])
		return (text);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*text;
	static char	*buff = NULL;

	if (fd < 0 || read(fd, buff, 0) == -1 || BUFFER_SIZE <= 0)
	{
		if (buff)
			free(buff);
		return (NULL);
	}
	if (!buff)
		buff = (char *)ft_calloc(1, 1);
	text = ft_strdup(buff);
	return (handle_line(fd, text, &buff));
}
