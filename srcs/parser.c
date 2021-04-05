/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:20:30 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/05 17:53:27 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			syntax_err(t_token **lexer, int	i)
{
	if (!lexer[i] && lexer[i - 1]->type > 0 && lexer[i - 1]->type < 5)
		ft_putstr_fd("multiline is currently not supported\n", 2);
	else if (!lexer[i] && lexer[i - 1]->type > 4 && lexer[i - 1]->type < 9)
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

int			find_separator(t_token **lexer)
{
	int		i;

	i = 0;
	while (lexer[i])
	{
		if (lexer[i]->type > 0 && lexer[i]->type < 4)
			break;
		i++;
	}
	return (i);
}

t_node	*ft_new_node(enum type type, t_list *cmd_lst)
{
	t_node	*node;

	if (!(node = ft_calloc(sizeof(t_node), 1)))
		return (NULL);
	node->type = type;
	node->cmd_lst = cmd_lst;
	return (node);
}

t_node		*build_node(t_token **lexer)
{
	int			i;
	t_list		*cmd_lst;
	t_cmd		*cmd;
	t_rdir		*rdir;

	i = 0;
	cmd_lst = NULL;
	rdir = NULL;
	if (!(cmd = ft_calloc(sizeof(t_cmd), 1)) || !(rdir = ft_calloc(sizeof(t_rdir), 1)))
		return (NULL);
	while (lexer[i])
	{
		if (lexer[i]->type == PIPE)
		{
			cmd->pipe_flag = 1;
			ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
			if (!(cmd = ft_calloc(sizeof(t_cmd), 1))) // prev. pointer was saved in the list content
				return (NULL);
		}
		else if (lexer[i]->type > 4 && lexer[i]->type < 9)
		{
			if (lexer[i]->type == RIGHT)
				rdir->flag = 1;
			else if (lexer[i]->type == LEFT)
				rdir->flag = 2;
			else if (lexer[i]->type == DRIGHT)
				rdir->flag = 3;
			else
				rdir->flag = 4;
			rdir->file = ft_strdup(lexer[i + 1]->s);
			ft_lstadd_back(&(cmd->rdir_lst), ft_lstnew(rdir));
		 	if (!(rdir = ft_calloc(sizeof(t_rdir), 1))) // prev. pointer was saved in the list content
				return (NULL);
			i++; // to skip both the redir token + the following token linked to it
		}
		else
			ft_lstadd_back(&(cmd->exec_lst), ft_lstnew(ft_strdup(lexer[i]->s))); // STRDUP car plus facile pour free derriere vu qu'on ne va plus utiliser lexer mais tjr les pointeurs qu'il contient
		i++;
	}
	ft_lstadd_back(&(cmd_lst), ft_lstnew(cmd));
	if (!(cmd_lst))
			return (NULL);
	return (ft_new_node(CMD, cmd_lst));
}

t_node		*build_tree(t_token **lexer, int i)
{
	t_node		*node;
	t_token		*tmp;

	node = NULL;
	if (lexer[i] == NULL) // if no sep is found then we have a simple cmd. 1 node = 1 cmd or 1 sep
		node = build_node(lexer);
	else if (lexer[i]->type > 0 && lexer[i]->type < 4)
	{
		node = ft_new_node(lexer[i]->type, NULL);
		tmp = lexer[i];          // we send the left part and treat it as a CMD
		lexer[i] = NULL;
		node->left = build_node(lexer);
		lexer[i] = tmp;
		node->right = parser(lexer + i + 1);
	}
	return (node);
}

t_node		*parser(t_token **lexer)
{
	t_node		*ast = NULL;
	int			i;

//	if (!lexer || syntax_check(lexer)) // call dans une autre fct ?
//		return (NULL);
	i = find_separator(lexer);
	ast = build_tree(lexer, i);
	return (ast);
}



/*
parser:
je split mon tableau de tokens dans des noeuds si necessaire
pour chaque noeud je remplis la structure cmd
j'utilise les infos des tokens pour remplir la section pipe et rdir
dans cmd les tokens deviennent un liste chainee de char *
*/