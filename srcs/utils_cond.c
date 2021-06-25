/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cond.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:31:52 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/25 16:49:02 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char *s, int i)
{
	if (((s[i] > 8 && s[i] < 14) || s[i] == ' ') && !is_escaped(s, i))
		return (1);
	return (0);
}

int	is_escaped(char *s, int pos)
{
	int		bs_flag;
	int		i;

	if (pos == 0)
		return (0);
	i = 0;
	bs_flag = 0;
	while (i <= pos)
	{
		bs_flag = 0;
		while (s[i] == '\\')
		{
			bs_flag++;
			i++;
		}
		i++;
	}
	if (bs_flag == 0)
		return (0);
	else if (bs_flag % 2 > 0)
		return (1);
	return (0);
}

int	is_special(char *s, int i)
{
	if (s[i] == '\0')
		return (0);
	if (((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<')
			|| (s[i] == '&' && s[i + 1] == '&')
			|| (s[i] == '|' && s[i + 1] == '|'))
		&& !is_escaped(s, i))
		return (2);
	else if ((s[i] == ';' || s[i] == '|' || s[i] == '>' || s[i] == '<')
		&& !is_escaped(s, i))
		return (1);
	else
		return (0);
}

int	is_defined(char *s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
