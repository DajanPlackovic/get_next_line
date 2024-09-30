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
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
int				ft_lstsize(t_list *lst);
size_t			ft_strlen(const char *s);

char	*build_line(t_list **buffer, t_list *last)
{
	char	*line;
	size_t	size;
	size_t	i;
	size_t	j;
	t_list	*curr;

	size = ft_lstsize(*buffer) * BUFFER_SIZE + ft_strlen(last->content) + 1;
	line = (char *)malloc(size);
	if (!line)
	{
		ft_lstclear(buffer, free);
		free(last->content);
		free(last);
		return (NULL);
	}
	curr = *buffer;
	j = 0;
	while (curr)
	{
		i = 0;
		while (curr->content[i])
		{
			line[j] = curr->content[i];
			i++;
			j++;
		}
		curr = curr->next;
	}
	i = 0;
	while (last->content[i])
	{
		line[j] = last->content[i];
		i++;
		j++;
	}
	line[j] = 0;
	ft_lstclear(buffer, free);
	if (strchr(last->content, '\n'))
    	*buffer = last;
	return (line);
}

static t_list	*read_into_buffer(int fd, t_list **buffer)
{
	t_list	*node;
	char	*content;
	ssize_t	bread;

	bread = BUFFER_SIZE;
	node = NULL;
	while (bread == BUFFER_SIZE)
	{
		if (node)
			ft_lstadd_back(buffer, node);
		content = (char *)malloc(BUFFER_SIZE + 1);
		if (!content)
		{
			ft_lstclear(buffer, free);
			return (NULL);
		}
		bread = -1;
		while (++bread < BUFFER_SIZE + 1)
			content[bread] = 0;
		bread = read(fd, content, BUFFER_SIZE);
		if (bread == 0)
			break ;
		node = ft_lstnew(content);
		if (!node)
		{
			free(content);
			ft_lstclear(buffer, free);
			return (NULL);
		}
		if (strchr(content, '\n'))
			break ;
	}
	return (node);
}

char	*get_next_line(int fd)
{
	static t_list	**buffer = NULL;
	t_list			*last;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (t_list **)malloc(sizeof(t_list *));
		if (!buffer)
			return (NULL);
		buffer[0] = 0;
	}
	last = read_into_buffer(fd, buffer);
	if (!last)
		return (NULL);
	return (build_line(buffer, last));
}
