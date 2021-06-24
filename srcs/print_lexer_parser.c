/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:33:36 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/24 20:26:18 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_lexer(t_token **lexer, char *s)
{
	int		i;

	i = 0;
	printf("ORIGINAL STRING: [%s]\n", s);
	printf("\n********************* L E X E R ***********************\n\n");
	while (lexer[i])
	{
		printf("lexer[%i]: type = [%i] | s = [%s]\n", i, lexer[i]->type, lexer[i]->s);
		i++;
	}
}

void	print_exec_lst(t_list *exec_lst)
{
	printf("exec_lst: ");
	if (!exec_lst)
		printf("(null)");
	while (exec_lst)
	{
		printf("[%s] ", ((char *)exec_lst->content));
		exec_lst = exec_lst->next;
	}
	printf("\n");
}

void	print_rdir_lst(t_list *rdir_lst)
{
	printf("rdir_lst: ");
	if (!rdir_lst)
		printf("(null)");
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
		printf("\n          ");
	}
	printf("\n");
}

void	print_cmd_lst(t_list *cmd_lst)
{
	int		i;

	i = 0;
	while (cmd_lst)
	{
		printf("\ncmd_lst: node {%i}\n", i);
		printf("pipe_flag = %i\n", ((t_cmd *)cmd_lst->content)->pipe_flag);
		print_exec_lst(((t_cmd *)cmd_lst->content)->exec_lst);
		print_rdir_lst(((t_cmd *)cmd_lst->content)->rdir_lst);
		cmd_lst = cmd_lst->next;
		i++;
	}
}

void	print_children(t_node *node, int tree_pos)
{
	printf("-------------------------------------------------------\n");
	if (node->left)
	{
		tree_pos++;
		printf("\nLEFT CHILD --------------------------------------------\n");
		print_ast_node(node->left, tree_pos);
	}
	if (node->right)
	{
		tree_pos++;
		printf("\nRIGHT CHILD -------------------------------------------\n");
		print_ast_node(node->right, tree_pos);
	}
}

void	print_ast_node(t_node *node, int tree_pos)
{
	if (!node)
		return;
	if (tree_pos == 0)
		printf("ROOT --------------------------------------------------\n");
	if (node->type == SEMICOLON)
	{
		printf("node->type = \';\'\n");
		print_children(node, tree_pos);
	}
	else if (node->type == AND)
	{
		printf("node->type = \'&&\'\n");
		print_children(node, tree_pos);
	}
	else if (node->type == OR)
	{
		printf("node->type = \'||\'\n");
		print_children(node, tree_pos);
	}
	else if (node->type == CMD)
	{
		printf("node->type = \'CMD\'\n");
		print_cmd_lst(node->cmd_lst);
		print_children(node, tree_pos);
	}
}

void	print_parser(t_node *ast)
{
	printf("\n********************* P A R S E R *********************\n\n");
	print_ast_node(ast, 0);
}