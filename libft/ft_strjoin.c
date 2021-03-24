/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:30:31 by vlugand-          #+#    #+#             */
/*   Updated: 2019/11/15 18:07:24 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_append(char *dst, char const *s, size_t *len)
{
	size_t		i;

	i = 0;
	while (s[i])
	{
		dst[*len] = s[i];
		i++;
		(*len)++;
	}
	return (dst);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*dst;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(dst = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	len = 0;
	ft_append(dst, s1, &len);
	ft_append(dst, s2, &len);
	dst[len] = '\0';
	return (dst);
}
