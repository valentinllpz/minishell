/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:39:42 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/24 14:16:56 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(char *s)
{
	t_token		*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
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
	else if (s[0] == '>' && s[1] == '>')
		token->type = DRIGHT;
	else if (s[0] == '<' && s[1] == '<')
		token->type = DLEFT;
	else if (s[0] == '>')
		token->type = RIGHT;
	else if (s[0] == '<')
		token->type = LEFT;
	return (token);
}

int	word_count(char *s)
{
	int			i;
	int			wc;

	i = 0;
	wc = 0;
	skip_spaces(s, &i);
	while (s[i])
	{
		if (s[i] && !is_space(s, i) && !is_special(s, i))
			wc++;
		while (s[i] && !is_space(s, i) && !is_special(s, i))
		{
			if ((s[i] == '\'' || s[i] == '\"') && !is_escaped(s, i))
				i = get_next_valid_quote_index(s, i);
			i++;
		}
		if (s[i] && (is_special(s, i) == 1 || is_special(s, i) == 2))
			wc++;
		i += is_special(s, i);
		while (s[i] && is_space(s, i))
			i++;
	}
	return (wc);
}

t_token	*build_token(char *s, int *i)
{
	int			len;
	char		*dst;

	len = *i;
	while (s[*i] && !is_space(s, *i) && !is_special(s, *i))
	{
		if ((s[*i] == '\'' || s[*i] == '\"') && !is_escaped(s, *i))
			*i = get_next_valid_quote_index(s, *i);
		(*i)++;
	}
	len = *i - len;
	if (s[*i] && (is_special(s, *i) == 1 || is_special(s, *i) == 2) && len == 0)
	{
		len = is_special(s, *i);
		*i += len;
	}
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s + (*i - len), (len + 1));
	return (new_token(dst));
}

t_token	**ft_lexer(char *s)
{
	int			i;
	int			j;
	t_token		**lexer;

	if (!s)
		return (NULL);
	lexer = malloc((1 + word_count(s)) * sizeof(t_token *));
	if (!lexer)
		return (NULL);
	i = 0;
	j = 0;
	skip_spaces(s, &i);
	while (s[i])
	{
		lexer[j] = build_token(s, &i);
		if (!(lexer[j]))
		{
			free_lexer(lexer);
			return (NULL);
		}
		skip_spaces(s, &i);
		j++;
	}
	lexer[j] = NULL;
	return (lexer);
}
