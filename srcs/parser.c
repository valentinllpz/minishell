/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:20:30 by vlugand-          #+#    #+#             */
/*   Updated: 2021/03/26 15:55:31 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			syntax_err(t_token **lexer, int	i)
{
	if (!lexer[i] && lexer[i - 1]->type > 0 && lexer[i - 1]->type < 5)
		ft_putstr_fd("multiline is currently not supported\n", 2);
	else if (!lexer[i] && lexer[i - 1]->type > 5 && lexer[i - 1]->type < 9)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(lexer[i]->s, 2);
		write(2, "'\n", 2);
	}
	free_lexer(lexer);
	return (0);
}

int			syntax_check(t_token **lexer)
{
	int		i;

	i = 0;
	if (lexer[i]->type > 0 && lexer[i]->type < 5)
		return (syntax_err(lexer, i));
	while (lexer[i])
	{
		if ((lexer[i]->type > 0 && lexer[i]->type < 5)
		&& ((!lexer[i + 1]) || (lexer[i + 1]->type > 0 && lexer[i + 1]->type < 5)))
			return (syntax_err(lexer, i + 1));
		else if ((lexer[i]->type > 4 && lexer[i]->type < 9) && (!lexer[i + 1] || lexer[i + 1]->type != WORD))
			return (syntax_err(lexer, i + 1));
		i++;
	}
	return (1);
}
/*
t_node		*parser(t_token **lexer)
{
	t_node		*ast = NULL;
	
	if (!lexer || syntax_check(lexer))
		return (NULL);
	return (ast);
}
*/