/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:20:30 by vlugand-          #+#    #+#             */
/*   Updated: 2021/03/25 12:24:58 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int			syntax_check(t_token **lexer)
{

}

t_node		*parser(t_token **lexer)
{
	t_node		*ast;
	
	if (!syntax_check(lexer))
		return (NULL);
	return (ast);
}
