/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:09:59 by vlugand-          #+#    #+#             */
/*   Updated: 2021/03/24 17:47:45 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int ac, char **av)
{
	t_token		**lexer;
	int			i; 

	i = 0;
	printf("original string: [%s]\n", av[1]);
	lexer = ft_lexer(av[1]);
	while (lexer[i])
	{
		printf("lexer[%i]: type = [%i] | s = [%s]\n", i, lexer[i]->type, lexer[i]->s);
		i++;
	}
	return (0);
}
