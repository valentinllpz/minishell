/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:57:58 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/22 19:00:10 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_dquotes_to_str(char *s)
{
	int		i;
	int		j;
	char	*dst;

	dst = malloc(sizeof(char) * (ft_strlen(s) + 2 + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 1;
	while (s[i])
	{
		dst[j] = s[i];
		i++;
		j++;
	}
	dst[0] = '\"';
	dst[j] = '\"';
	dst[j + 1] = '\0';
	free(s);
	return (dst);
}

char	*preserve_literal_value(char *match, int dq_flag)
{
	int		i;
	int		j;
	char	*dst;

	dst = malloc(sizeof(char) * (ft_strlen(match) * 2 + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (match[i])
	{
		if ((is_space(match, i) && dq_flag) || !is_space(match, i))
		{
			dst[j] = '\\';
			j++;
		}
		dst[j] = match[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	if (dq_flag)
		return (add_dquotes_to_str(dst));
	return (dst);
}
