/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:20:30 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/09 15:41:14 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			add_to_cmd_lst(t_cmd **cmd, t_list **cmd_lst, int pipe_flag)
{
	(*cmd)->pipe_flag = pipe_flag;
	ft_lstadd_back(cmd_lst, ft_lstnew(*cmd));
	if (pipe_flag && (!(*cmd = ft_calloc(sizeof(t_cmd), 1)) || !(*cmd_lst)))// prev. pointer was saved in the list content
		return (0);
	return (1);
}

int			add_to_rdir_lst(t_token **lexer, int *i, t_cmd *cmd)
{
	t_rdir		*rdir;

	rdir = NULL;
	if (!(rdir = ft_calloc(sizeof(t_rdir), 1)))// prev. pointer was saved in the list content
		return (0);
	if (lexer[*i]->type == RIGHT)
		rdir->flag = 1;
	else if (lexer[*i]->type == LEFT)
		rdir->flag = 2;
	else if (lexer[*i]->type == DRIGHT)
		rdir->flag = 3;
	else
		rdir->flag = 4;
	(*i)++;
	rdir->file = ft_strdup(lexer[*i]->s);
	ft_lstadd_back(&(cmd->rdir_lst), ft_lstnew(rdir));
	if (!(cmd->rdir_lst))
		return (0);
	return (1);
}

int			add_to_exec_lst(t_token **lexer, t_cmd *cmd, int i)
{
	ft_lstadd_back(&(cmd->exec_lst), ft_lstnew(ft_strdup(lexer[i]->s)));
	if (!cmd->exec_lst)
		return (0);
	return (1);
}

t_node		*build_node(t_token **lexer)
{
	int			i;
	int			ret;
	t_list		*cmd_lst;
	t_cmd		*cmd;

	i = 0;
	cmd_lst = NULL;
	if (!(cmd = ft_calloc(sizeof(t_cmd), 1)))
		return (NULL);
	while (lexer[i])
	{
		if (lexer[i]->type == PIPE)
			ret = add_to_cmd_lst(&cmd, &cmd_lst, 1);
		else if (lexer[i]->type > 4 && lexer[i]->type < 9)
			ret = add_to_rdir_lst(lexer, &i, cmd);
		else
			ret = add_to_exec_lst(lexer, cmd, i);// STRDUP car plus facile pour free derriere vu qu'on ne va plus utiliser lexer mais tjr les pointeurs qu'il contient
		if (!ret)
			return (NULL);
		i++;
	}
	ret = add_to_cmd_lst(&cmd, &cmd_lst, 0);
	if (!ret)
		return (NULL);
	return (ft_new_node(CMD, cmd_lst));
}

t_node		*build_tree(t_token **lexer)
{
	int			i;
	t_node		*node;
	t_token		*tmp;

	node = NULL;
	i = find_separator(lexer);
	if (lexer[i] == NULL)// if no sep is found then we have a simple cmd. 1 node = 1 cmd or 1 sep
		node = build_node(lexer);
	else if (lexer[i]->type > 0 && lexer[i]->type < 4)
	{
		node = ft_new_node(lexer[i]->type, NULL);
		tmp = lexer[i];// we send the left part and treat it as a CMD
		lexer[i] = NULL;
		node->left = build_node(lexer);
		lexer[i] = tmp;
		node->right = build_tree(lexer + i + 1);
	}
	return (node);
}
