/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dplackov <dplackov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:01:21 by dplackov          #+#    #+#             */
/*   Updated: 2024/09/14 17:10:29 by dplackov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	int		s1_len;
	int		total_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1) + 1;
	total_len = s1_len + ft_strlen(s2);
	out = (char *)ft_calloc(total_len, 1);
	if (!out)
		return (NULL);
	ft_strlcpy(out, s1, s1_len);
	ft_strlcat(out, s2, total_len);
	return (out);
}
