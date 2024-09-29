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
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char	*ft_strjoin_free(char **s1, char **s2)
{
	char	*out;
	int		s1_len;
	int		total_len;

	if (!*s1 || !*s2)
		return (NULL);
	s1_len = ft_strlen(*s1) + 1;
	total_len = s1_len + ft_strlen(*s2);
	out = (char *)ft_calloc(total_len, 1);
	if (!out)
	{
		free((void *)*s1);
		return (NULL);
	}
	ft_strlcpy(out, *s1, s1_len);
	ft_strlcat(out, *s2, total_len);
	free((void *)*s1);
	return (out);
}

static int	setup(char **buff, char **text)
{
	if (*buff)
	{
		*text = strdup(*buff);
		if (!*text)
		{
			free(*buff);
			*buff = NULL;
			return (0);
		}
	}
	else
	{
		*text = calloc(1, 1);
	}
	*buff = calloc(BUFFER_SIZE, 1);
	if (!*buff)
	{
		free(text);
		return (0);
	}
	return (1);
}

static int	read_file(int fd, char **buff, char **text)
{
	ssize_t	bread;

	bread = 1;
	while (bread > 0)
	{
		bread = read(fd, *buff, BUFFER_SIZE);
		if (!bread)
			break ;
		*text = ft_strjoin_free(text, buff);
		if (!*text)
		{
			free(*buff);
			buff = NULL;
			return (0);
		}
		if (strchr(*text, '\n'))
			return (1);
	}
	free(*buff);
	*buff = NULL;
	return (1);
}

char	*get_next_line(int fd)
{
	ssize_t		bread;
	static char	*buff = NULL;
	char		*text;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!setup(&buff, &text))
		return (NULL);
	if (!read_file(fd, &buff, &text))
		return (NULL);
	if (text[0])
		return (text);
	free(text);
	return (NULL);
}
