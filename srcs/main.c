/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:09:59 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/07 15:19:10 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int ac, char **av)
{
	t_token		**lexer;
	t_node		*ast;

	(void)ac;
	if (!(lexer = ft_lexer(av[1])))
		return (0); 
	print_lexer(lexer, av[1]); // print to debug
	if(!(ast = parser(lexer)))
		return (0);
	print_parser(ast); // print to debug
//	while (1) {} // uncomment to test leaks on mac os
	return (0);
}

/*ATTENTION VAR 

check les chifres et symboles spe
difference avec ou sans export
peut concat avec +=
*/