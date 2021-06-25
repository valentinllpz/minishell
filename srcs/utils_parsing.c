/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:18:40 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/25 17:19:05 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_spaces(char *s, int *i)
{
	while (s[*i] && ((s[*i] > 8 && s[*i] < 14) || s[*i] == ' '))
		(*i)++;
}

int	get_next_valid_quote_index(char *s, int i)
{
	int		start;

	start = i;
	if (s[i] == '\'' && !is_escaped(s, i))
	{
		i++;
		while (s[i])
		{
			if (s[i] == '\'' && !is_escaped(s, i))
				return (i);
			i++;
		}
	}
	else if (s[i] == '\"' && !is_escaped(s, i))
	{
		i++;
		while (s[i])
		{
			if (s[i] == '\"' && !is_escaped(s, i))
				return (i);
			i++;
		}
	}
	return (start);
}

char	*join_three_str(char *s1, char *s2, char *s3)
{
	int		len1;
	int		len2;
	int		len3;
	char	*dst;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	if (s3)
		len3 = ft_strlen(s3);
	else
		len3 = 0;
	dst = malloc((len1 + len2 + len3 + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, len1 + 1);
	ft_strlcpy(dst + len1, s2, len2 + 1);
	ft_strlcpy(dst + len1 + len2, s3, len3 + 1);
	return (dst);
}
