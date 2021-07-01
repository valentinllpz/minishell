/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:26:58 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/01 11:07:57 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_err(t_token **lexer, int i)
{
	if (!lexer[i] && lexer[i - 1]->type > 0 && lexer[i - 1]->type < 5)
		ft_putstr_fd("minishell: multiline is currently not supported\n", 2);
	else if (!lexer[i] && lexer[i - 1]->type > 4 && lexer[i - 1]->type < 9)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(lexer[i]->s, 2);
		write(2, "'\n", 2);
	}
	free_lexer(lexer);
	return (0);
}

int	syntax_check(t_token **lexer)
{
	int			i;

	i = 0;
	if (lexer[i]->type > 0 && lexer[i]->type < 5)
		return (syntax_err(lexer, i));
	while (lexer[i])
	{
		if ((lexer[i]->type > 0 && lexer[i]->type < 5) && ((!lexer[i + 1])
				|| (lexer[i + 1]->type > 0 && lexer[i + 1]->type < 5)))
			return (syntax_err(lexer, i + 1));
		else if ((lexer[i]->type > 4 && lexer[i]->type < 9) && (!lexer[i + 1]
				|| lexer[i + 1]->type != WORD))
			return (syntax_err(lexer, i + 1));
		i++;
	}
	return (1);
}

int	find_separator(t_token **lexer)
{
	int			i;

	i = 0;
	while (lexer[i])
	{
		if (lexer[i]->type > 0 && lexer[i]->type < 4)
			return (i);
		i++;
	}
	return (i);
}

t_node	*ft_new_node(enum e_type type, t_list *cmd_lst)
{
	t_node		*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd_lst = cmd_lst;
	return (node);
}

t_node	*parser(t_token **lexer)
{
	t_node		*ast;

	if (!lexer)
		return (NULL);
	if (!syntax_check(lexer))
		return (NULL);
	ast = build_tree(lexer);
	free_lexer(lexer);
	return (ast);
}
