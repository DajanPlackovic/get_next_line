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
	char			*text;
	static char		*buff = 0;
	static ssize_t	bread = 1;
	char			*pos;
	char			*out;

	if (!buff)
		buff = (char *)ft_calloc(1, 1);
	text = ft_strdup(buff);
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
