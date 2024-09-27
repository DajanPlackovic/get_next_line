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

#include "libft.h"
#include <unistd.h>

char	*get_next_line(int fd)
{
	char		*text;
	static char	*buff = 0;
	ssize_t		bread;
	char		*pos;
	char		*out;

	if (fd < 0 || read(fd, buff, 0) == -1)
		return (NULL);
	if (!buff)
		buff = (char *)ft_calloc(1, 1);
	text = ft_strdup(buff);
	bread = 1;
	while (bread > 0)
	{
		pos = ft_strchr(text, '\n');
		if (pos)
		{
			out = ft_substr(text, 0, pos - text + 1);
			buff = ft_substr(text, pos - text + 1, ft_strlen(text) - (pos - text
						+ 1));
			free(text);
			return (out);
		}
		else
		{
			bread = read(fd, buff, BUFFER_SIZE);
			text = ft_strjoin(text, buff);
		}
	}
	free(text);
	free(buff);
	return (NULL);
}
