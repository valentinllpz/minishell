/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:22:39 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/15 18:45:43 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		len_after_bs_rm(char *s)
{
	int		i;
	int		len;
	int		bs;

	i = 0;
	len = 0;
	bs = 0;
	while (s[i])
	{
		bs = 0;
		if (s[i] != '\\')
		{
			i++;
			len++;
		}
		while (s[i] == '\\')
		{
			bs++;
			i++;
		}
		if (bs > 0)
			len += bs / 2;
	}
	return (len);
}

void	add_escaped_bs(char *s, char *dst, int *i, int *j)
{
	int		bs;

	bs = 0;
	while (s[*i] == '\\')
	{
		bs++;
		(*i)++;
	}
	if (bs > 0)
	{
		bs = bs / 2;
		while (bs > 0)
		{
			dst[*j] = '\\';
			bs--;
			j++;
		}
	}
}

char	*backslash_rm(char *s)
{
	int		i;
	int		j;
	char	*dst;

	dst = malloc(sizeof(char) * (len_after_bs_rm(s) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\\')
		{
			dst[j] = s[i];
			j++;
			i++;
		}
		else
			add_escaped_bs(s, dst, &i, &j);
	}
	dst[j] = '\0';
	free(s);
	return (dst);
}
