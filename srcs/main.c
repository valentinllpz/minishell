/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:09:59 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/17 15:29:26 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int ac, char **av)
{
	t_token		**lexer;
	t_node		*ast;

	(void)ac;
	if (!(lexer = ft_lexer(av[1])))
		return (1); 
	print_lexer(lexer, av[1]); // print to debug
	if(!(ast = parser(lexer)))
		return (1);
	print_parser(ast); // print to debug
	free_ast(ast); // free_ast(ast, 1);
//	system("leaks minishell");// uncomment to test leaks on mac os
	return (0);
}
