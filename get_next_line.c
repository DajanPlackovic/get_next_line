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

size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strchr(const char *s, char c);
char		*ft_strjoin(char **s1, char **s2);

static int	read_file(int fd, char **buff, char **text)
{
	ssize_t	bread;

	bread = 1;
	while (bread > 0)
	{
		bread = -1;
		while (++bread < BUFFER_SIZE)
			(*buff)[bread] = 0;
		bread = read(fd, *buff, BUFFER_SIZE);
		if (bread < 0)
			return (0);
		*text = ft_strjoin(text, buff);
		if (!*text)
			return (0);
		if (ft_strchr(*text, '\n'))
			return (1);
	}
	free(*buff);
	*buff = NULL;
	return (1);
}

static int	prep_text(char **buff, char **text)
{
	if (*buff)
	{
		*text = ft_substr(*buff, 0, ft_strlen(*buff));
		if (!*text)
		{
			free(*buff);
			*buff = NULL;
			return (0);
		}
	}
	else
	{
		*text = ft_calloc(1, 1);
		if (!*text)
			return (0);
	}
	return (1);
}

static int	prep_buff(int fd, char **text, char **buff)
{
	if (*buff)
		free(*buff);
	*buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!*buff)
	{
		free(*text);
		return (0);
	}
	if (!read_file(fd, buff, text))
	{
		if (*text)
			free(*text);
		free(*buff);
		*buff = NULL;
		return (0);
	}
	return (1);
}

char	*extract_line(char **buff, char **text)
{
	char	*nl_pos;
	char	*line;

	nl_pos = ft_strchr(*text, '\n');
	if (nl_pos)
	{
		line = ft_substr(*text, 0, nl_pos - *text + 1);
		if (*buff)
			free(*buff);
		if (!line || !*(nl_pos + 1))
			*buff = NULL;
		else
			*buff = ft_substr(*text, nl_pos - *text + 1, ft_strlen(*text));
		free(*text);
		return (line);
	}
	else
	{
		if (*buff)
			free(*buff);
		*buff = NULL;
		return (*text);
	}
}

char	*get_next_line(int fd)
{
	static char	*buff = NULL;
	char		*text;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (buff)
		{
			free(buff);
			buff = NULL;
		}
		return (NULL);
	}
	if (!prep_text(&buff, &text))
		return (NULL);
	if (!prep_buff(fd, &text, &buff))
		return (NULL);
	if (text[0])
		return (extract_line(&buff, &text));
	free(text);
	free(buff);
	buff = NULL;
	return (NULL);
}
