/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:45:20 by vlugand-          #+#    #+#             */
/*   Updated: 2019/11/15 13:33:24 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_sep(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int		ft_strtrim_len(char const *s1, char const *set)
{
	int		i;
	int		sep;
	int		total;

	i = 0;
	sep = 0;
	while (s1[i] && ft_is_sep(s1[i], set))
	{
		i++;
		sep++;
	}
	while (s1[i])
		i++;
	total = i;
	i--;
	while (i > 0 && ft_is_sep(s1[i], set))
	{
		sep++;
		i--;
	}
	return (total - sep);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*dst;

	if (!s1)
		return (ft_strdup(""));
	len = ft_strtrim_len(s1, set);
	if (len <= 0)
		return (ft_strdup(""));
	if (!(dst = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && ft_is_sep(s1[i], set))
		i++;
	while (j < len)
	{
		dst[j] = s1[i];
		j++;
		i++;
	}
	dst[len] = '\0';
	return (dst);
}
