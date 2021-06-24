/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:07:48 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/24 10:34:05 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_separator(char const *s, size_t *i, char c)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t		i;
	size_t		wc;

	i = 0;
	wc = 0;
	skip_separator(s, &i, c);
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		skip_separator(s, &i, c);
		wc++;
	}
	return (wc);
}

static char	*ft_make_str(char const *s, char c)
{
	size_t		i;
	char		*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
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

static char	**ft_freeall(char **split)
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

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		j;
	char		**split;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc((1 + ft_word_count(s, c)) * sizeof(char *));
	if (!split)
		return (NULL);
	skip_separator(s, &i, c);
	while (s[i])
	{
		split[j] = ft_make_str(s + i, c);
		if (!(split[j]))
			return (ft_freeall(split));
		while (s[i] && s[i] != c)
			i++;
		skip_separator(s, &i, c);
		j++;
	}
	split[j] = NULL;
	return (split);
}
