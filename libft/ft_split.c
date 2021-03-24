/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:07:48 by vlugand-          #+#    #+#             */
/*   Updated: 2019/11/15 13:33:56 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(char const *s, char c)
{
	size_t		i;
	size_t		wc;

	i = 0;
	wc = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
		wc++;
	}
	return (wc);
}

static char		*ft_make_str(char const *s, char c)
{
	size_t		i;
	char		*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(str = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char		**ft_freeall(char **split)
{
	size_t		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		j;
	char		**split;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(split = (char**)malloc((1 + ft_word_count(s, c)) * sizeof(char *))))
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (!(split[j] = ft_make_str(s + i, c)))
			return (ft_freeall(split));
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
		j++;
	}
	split[j] = NULL;
	return (split);
}
