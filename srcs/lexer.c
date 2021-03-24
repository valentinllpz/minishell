/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:39:42 by vlugand-          #+#    #+#             */
/*   Updated: 2021/03/24 17:57:06 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token		*new_token(char *s)
{
	t_token		*token;

	if (!(token = ft_calloc(sizeof(t_token), 1)))
		return (NULL);
	if (s)
	{
		token->s = s;
		if (s[0] == '&' && s[1] == '&')
			token->type = AND;
		else if (s[0] == '|' && s[1] == '|')
			token->type = OR;
		else if (s[0] == ';')
			token->type = SEMICOLON;
		else if (s[0] == '|')
			token->type = PIPE;
		else if (s[0] == '>')
			token->type = RIGHT;
		else if (s[0] == '<')
			token->type = LEFT;
		else if (s[0] == '>' && s[1] == '>')
			token->type = DRIGHT;
		else if (s[0] == '<' && s[1] == '<')
			token->type = LEFT;
	}
	return (token);
}

static void			skip_to_next_valid_quote(char *s, int *i)
{
	if (s[*i] && !is_escaped('\'', s, *i))
	{
		(*i)++;
		while (s[*i])
		{
			if (s[*i] == '\'' && !is_escaped('\'', s, *i))
				break ;
			(*i)++;
		}
	}
	else if (s[*i] && !is_escaped('\"', s, *i))
	{
		(*i)++;
		while (s[*i])
		{
			if (s[*i] == '\"' && !is_escaped('\"', s, *i))
				break ;
			(*i)++;
		}
	}
}

static t_token		*build_token(char *s)
{
	int			len;
	char		*dst;
	int			i;

	len = 0;
	while (s[len])
	{
		if (s[len] == '\'' || s[len] == '\"')
			skip_to_next_valid_quote(s, &len);
		if (is_space(s[len]))
			break ;
		len++;
	}
	if (!(dst = malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < len)
		dst[i] = s[i];
	dst[i] = '\0';
	return (new_token(dst));
}

static int			word_count(char *s)
{
	int			i;
	int			wc;

	i = 0;
	wc = 0;
	skip_spaces(s, &i);
	while (s[i])
	{
		while (s[i] && !is_space(s[i]))
		{
			if (s[i] == '\'' || s[i] == '\"')
				skip_to_next_valid_quote(s, &i);
			i++;
		}
		while (s[i] && is_space(s[i]))
			i++;
		wc++;
	}
	return (wc);
}

t_token				**ft_lexer(char *s)
{
	int			i;
	int			j;
	t_token		**lexer;

	i = 0;
	j = 0;
	if (!s || !(lexer = malloc((1 + word_count(s)) * sizeof(t_token *))))
		return (NULL);
	skip_spaces(s, &i);
	while (s[i])
	{
		if (!(lexer[j] = build_token(s + i)))
			return (free_lexer(lexer));
		while (s[i] && !is_space(s[i]))
		{
			if (s[i] == '\'' || s[i] == '\"')
				skip_to_next_valid_quote(s, &i);
			i++;
		}
		while (s[i] && is_space(s[i]))
			i++;
		j++;
	}
	lexer[j] = NULL;
	return (lexer);
}
