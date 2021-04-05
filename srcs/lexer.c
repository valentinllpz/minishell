/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:39:42 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/05 14:36:45 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token			*new_token(char *s)
{
	t_token		*token;

	if (!(token = ft_calloc(sizeof(t_token), 1)))
		return (NULL);
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
	return (token);
}

void			skip_to_next_valid_quote(char *s, int *i)
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

int				word_count(char *s)
{
	int			i;
	int			wc;

	i = 0;
	wc = 0;
	skip_spaces(s, &i);
	while (s[i])
	{
		if (s[i] && !is_space(s[i]) && !is_special(s, i))
			wc++;
		while (s[i] && !is_space(s[i]) && !is_special(s, i))
		{
			if (s[i] == '\'' || s[i] == '\"')
				skip_to_next_valid_quote(s, &i);
			i++;
		}
		if (s[i] && (is_special(s, i) == 1 || is_special(s, i) == 2))
			wc++;
		i += is_special(s, i);
		while (s[i] && is_space(s[i]))
			i++;
	}
	return (wc);
}

t_token			*build_token(char *s, int *i)
{
	int			len;
	char		*dst;

	len = 0;
	while (s[*i] && !is_space(s[*i]) && !is_special(s, *i))
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			skip_to_next_valid_quote(s, i);
		(*i)++;
		len++;
	}
	if (s[*i] && (is_special(s, *i) == 1 || is_special(s, *i) == 2) && len == 0)
	{
		len = is_special(s, *i);
		*i += len;
	}
	if (!(dst = malloc((len + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(dst, s + (*i - len), (len + 1));
	return (new_token(dst));
}

t_token			**ft_lexer(char *s)
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
		if (!(lexer[j] = build_token(s, &i)))
			return (free_lexer(lexer));
		skip_spaces(s, &i);
		j++;
	}
	lexer[j] = NULL;
	return (lexer);
}
