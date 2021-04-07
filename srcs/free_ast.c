/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:33:39 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/07 18:12:10 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_rdir(t_rdir *rdir)
{
	free(rdir->file);
	free(rdir);
}

void	free_cmd(t_cmd *cmd)
{
	while (cmd->exec_lst)
	{
		free(((char *)cmd->exec_lst->content));
		free(cmd->exec_lst);
		cmd->exec_lst = cmd->exec_lst->next;
	}
	while (cmd->rdir_lst)
	{
		free_rdir(cmd->rdir_lst->content);
		free(cmd->rdir_lst);
		cmd->rdir_lst = cmd->rdir_lst->next; 
	}
	free(cmd);
}

void	free_cmd_lst(t_list *cmd_lst)
{
	while (cmd_lst)
	{
		free_cmd(cmd_lst->content);
		cmd_lst = cmd_lst->next;
	}	
}

void	free_node(t_node *node)
{
	free_cmd_lst(node->cmd_lst);
	free(node);
}

void	free_ast(t_node *ast)
{
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	free_node(ast);
}
