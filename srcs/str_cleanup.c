/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:55:50 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/24 11:44:22 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rm_backslash_outside_quotes(char *s, char *dst, int *i, int *j)
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
			(*j)++;
		}
	}
}

void	rm_backslash_in_dquotes(char *s, char *dst, int *i, int *j)
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
		if (bs % 2 != 0 && (!(s[*i] == '$' || s[*i] == '`'
					|| s[*i] == '~' || s[*i] == '\"')))
			bs = (bs / 2) + 1;
		else
			bs = (bs / 2);
		while (bs > 0)
		{
			dst[*j] = '\\';
			bs--;
			(*j)++;
		}
	}
}

void	rm_quotes(char *s, char *dst, int *i, int *j)
{
	int		flag;

	flag = 0;
	if (s[*i] == '\'')
		flag = 1;
	else if (s[*i] == '\"')
		flag = 2;
	(*i)++;
	while (s[*i])
	{
		if ((s[*i] == '\'' && !is_escaped(s, *i) && flag == 1)
			|| (s[*i] == '\"' && !is_escaped(s, *i) && flag == 2))
		{
			(*i)++;
			break ;
		}
		else if (s[*i] == '\\' && flag == 2)
			rm_backslash_in_dquotes(s, dst, i, j);
		else
		{
			dst[*j] = s[*i];
			(*i)++;
			(*j)++;
		}
	}
}

char	*str_cleanup(char *s)
{
	int		i;
	int		j;
	char	*dst;

	dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\\')
			rm_backslash_outside_quotes(s, dst, &i, &j);
		else if ((s[i] == '\'' || s[i] == '\"') && !is_escaped(s, i))
			rm_quotes(s, dst, &i, &j);
		else
		{
			dst[j] = s[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
	free(s);
	return (dst);
}
