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
