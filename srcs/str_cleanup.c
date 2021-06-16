/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:55:50 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/16 19:28:28 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	bs_no_quotes(char *s, char *dst, int *i, int *j)
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

void	bs_in_dquotes(char *s, char *dst, int *i, int *j)
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
		if (bs % 2 != 0 && (!(s[*i] == '$' || s[*i] == '`' || s[*i] == '~')))
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

char	*rm_backslash(char *s, char *dst, int flag)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\\' || (s[i] == '\\' && flag == 1))
		{
			dst[j] = s[i];
			j++;
			i++;
		}
		else if (s[i] == '\\' && flag == 0)
			bs_no_quotes(s, dst, &i, &j);
		else if (s[i] == '\\' && flag == 2)
			bs_in_dquotes(s, dst, &i, &j);
	}
	dst[j] = '\0';
	return (dst);
}

char	*rm_quotes(char *s)
{
	int		i;

	i = 1;
	while (s[i])
	{
		if (s[i + 1])
			s[i - 1] = s[i];
		else
			s[i - 1] = '\0';
		i++;
	}
	return (s);	
}

char	*str_cleanup(char *s)
{
	int		i;
	int		flag;
	char	*dst;

	i = 0;
	flag = 0;
	if (s && s[0] == '\'')
		flag = 1;
	else if (s && s[0] == '\"')
		flag = 2;
	if (flag > 0)
		rm_quotes(s);
	dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dst)
		return (NULL);
	dst = rm_backslash(s, dst, flag);
	free(s);
	return (dst);
}
