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

size_t		ft_strlen_utils(const char *s);
void		*ft_calloc_utils(size_t nmemb, size_t size);
char		*ft_substr_utils(char const *s, unsigned int start, size_t len);
char		*ft_strchr_utils(const char *s, char c);

static char	*ft_strjoin_free(char **s1, char **s2)
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
		if (ft_strchr_utils(*text, '\n'))
			return (1);
	}
	free(*buff);
	*buff = NULL;
	return (1);
}

static int	setup(int fd, char **buff, char **text)
{
	if (*buff)
	{
		*text = ft_substr_utils(*buff, 0, BUFFER_SIZE);
		if (!*text)
		{
			free(*buff);
			*buff = NULL;
			return (0);
		}
	}
	else
	{
		*text = ft_calloc_utils(1, 1);
		if (!*text)
			return (0);
	}
	if (ft_strchr_utils(*text, '\n'))
	{
		free(*buff);
		*buff = NULL;
		return (1);
	}
	free(*buff);
	*buff = ft_calloc_utils(BUFFER_SIZE + 1, 1);
	if (!*buff)
	{
		free(*text);
		return (0);
	}
	if (!read_file(fd, buff, text))
		return (0);
	return (1);
}

char	*extract_line(char **buff, char **text)
{
	char	*nl_pos;
	char	*line;

	nl_pos = ft_strchr_utils(*text, '\n');
	if (nl_pos)
	{
		line = ft_substr_utils(*text, 0, nl_pos - *text + 1);
		free(*buff);
		if (!*(nl_pos + 1))
			*buff = NULL;
		else
			*buff = ft_substr_utils(*text, nl_pos - *text + 1, BUFFER_SIZE);
		free(*text);
		return (line);
	}
	else
	{
		free(*buff);
		*buff = NULL;
		return (*text);
	}
}

char	*get_next_line(int fd)
{
	static char	*buff = NULL;
	char		*text;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!setup(fd, &buff, &text))
		return (NULL);
	if (text[0])
		return (extract_line(&buff, &text));
	free(text);
	free(buff);
	buff = NULL;
	return (NULL);
}
