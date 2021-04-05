/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:09:59 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/05 17:57:57 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_exec_lst(t_list *exec_lst)
{
	printf("exec_lst: ");
	while (exec_lst)
	{
		printf("[%s] ", exec_lst->content);
		exec_lst = exec_lst->next;
	}
	printf("\n");
}

void	print_rdir_lst(t_list *rdir_lst)
{
	printf("rdir_lst: ");
	while (rdir_lst)
	{
		if (((t_rdir *)rdir_lst->content)->flag == 1)
			printf("flag = [>] |");
		else if (((t_rdir *)rdir_lst->content)->flag == 2)
			printf("flag = [<] |");
		else if (((t_rdir *)rdir_lst->content)->flag == 3)
			printf("flag = [>>] |");
		else if (((t_rdir *)rdir_lst->content)->flag == 4)
			printf("flag = [<<] |");
		printf(" file = [%s]", ((t_rdir *)rdir_lst->content)->file);
		rdir_lst = rdir_lst->next;
	}
	printf("\n");
}

void	print_ast_node(t_node *node)
{
	int		i;

	i = 0;
	if (!node)
		return;
	if (node->type == SEMICOLON)
	{
		printf("node->type = \';\'\n");
		print_ast_node(node->left);
	}
	else if (node->type == AND)
	{
		printf("node->type = \'&&\'\n");
		print_ast_node(node->left);
	}
	else if (node->type == OR)
	{
		printf("node->type = \'||\'\n");
		print_ast_node(node->left);
	}
	else if (node->type == CMD)
	{
		printf("node->type = \'CMD\'\n");
		while(node->cmd_lst)
		{
			printf("\ncmd_lst: node {%i}\n", i);
			printf("pipe_flag = %i\n", ((t_cmd *)node->cmd_lst->content)->pipe_flag);
			print_exec_lst(((t_cmd *)node->cmd_lst->content)->exec_lst);
			print_rdir_lst(((t_cmd *)node->cmd_lst->content)->rdir_lst);
			node->cmd_lst = node->cmd_lst->next;
			i++;
		}
		print_ast_node(node->left);
	}
}

int		main(int ac, char **av)
{
	t_token		**lexer;
	t_node		*ast;
	int			i; 

	i = 0;
	(void)ac;
	printf("original string: [%s]\n", av[1]);
	printf("wc: %i\n", word_count(av[1]));
	lexer = ft_lexer(av[1]); 
	if (!syntax_check(lexer))
		return (1);
	printf("\n****************** LEXER ******************\n\n");
	while (lexer[i])
	{
		printf("lexer[%i]: type = [%i] | s = [%s]\n", i, lexer[i]->type, lexer[i]->s);
		i++;
	}
	ast = parser(lexer);
	printf("\n****************** PARSER *****************\n\n");
	print_ast_node(ast);
	return (0);
}

/*ATTENTION VAR 

check les chifres et symboles spe
difference avec ou sans export
peut concat avec +=
*/