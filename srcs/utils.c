/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:52:26 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/09 12:05:17 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (1);
	return (0);	
}

int		is_escaped(char c, char *s, int i)
{
	if (s[i] == c && i == 0)
		return (0);
	else if (s[i] == c && i > 0 && s[i - 1] != '\\')
		return (0);
	return (1);
}

int			is_special(char *s, int i)
{
	if (s[i] == '\0')
		return (0);
	if (((s[i] == '>' && s[i + 1] == '>') || (s[i] == '&' && s[i + 1] == '&') ||
	(s[i] == '|' && s[i + 1] == '|')) && !is_escaped(s[i], s, i))
		return (2);
	else if ((s[i] == ';' || s [i] == '|' || s[i] == '>' || s[i] == '<') && !is_escaped(s[i], s, i))
		return (1);
	else
		return (0);
}

int		which_operator(char *s, int i)
{
	if (s[i] == '\0')
		return (0);
	if (s[i] == '&' && s[i + 1] == '&')
		return (AND);
	else if (s[i] == '|' && s[i + 1] == '|')
		return (OR);
	else if (s[i] == ';')
		return (SEMICOLON);
	else if (s[i] == '|')
		return (PIPE);
	else if (s[i] == '>')
		return (RIGHT);
	else if (s[i] == '<')
		return (LEFT);
	else if (s[i] == '>' && s[i + 1] == '>')
		return (DRIGHT);
	else if (s[i] == '<' && s[i + 1] == '<')
		return (DLEFT);
	else
		return (0);
}

void	skip_spaces(char *s, int *i)
{
	while (s[*i] && ((s[*i] > 8 && s[*i] < 14) || s[*i] == ' '))
		(*i)++;
}

t_token		**free_lexer(t_token **lexer)
{
	int			i;

	i = 0;
	while (lexer[i])
	{
		free(lexer[i]->s);
		free(lexer[i]);
		i++;
	}
	free(lexer);
	return (NULL);
}
/*
int		find_index(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
*/