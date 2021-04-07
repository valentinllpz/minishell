/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:52:26 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/07 17:18:31 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (1);
	return (0);	
}

int		is_escaped(char c, char *s, int i)
{
	if (s[i] == c && i == 0)
		return (0);
	else if (s[i] == c && i > 0 && s[i - 1] != '\\')
		return (0);
	return (1);
}

int			is_special(char *s, int i)
{
	if (s[i] == '\0')
		return (0);
	if (((s[i] == '>' && s[i + 1] == '>') || (s[i] == '&' && s[i + 1] == '&') ||
	(s[i] == '|' && s[i + 1] == '|')) && !is_escaped(s[i], s, i))
		return (2);
	else if ((s[i] == ';' || s [i] == '|' || s[i] == '>' || s[i] == '<') && !is_escaped(s[i], s, i))
		return (1);
	else
		return (0);
}

int		which_operator(char *s, int i)
{
	if (s[i] == '\0')
		return (0);
	if (s[i] == '&' && s[i + 1] == '&')
		return (AND);
	else if (s[i] == '|' && s[i + 1] == '|')
		return (OR);
	else if (s[i] == ';')
		return (SEMICOLON);
	else if (s[i] == '|')
		return (PIPE);
	else if (s[i] == '>')
		return (RIGHT);
	else if (s[i] == '<')
		return (LEFT);
	else if (s[i] == '>' && s[i + 1] == '>')
		return (DRIGHT);
	else if (s[i] == '<' && s[i + 1] == '<')
		return (DLEFT);
	else
		return (0);
}

void	skip_spaces(char *s, int *i)
{
	while (s[*i] && ((s[*i] > 8 && s[*i] < 14) || s[*i] == ' '))
		(*i)++;
}

t_token		**free_lexer(t_token **lexer)
{
	int			i;

	i = 0;
	while (lexer[i])
	{
		free(lexer[i]->s);
		free(lexer[i]);
		i++;
	}
	free(lexer);
	return (NULL);
}

/*
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
*/
/*
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
		tmp = lexer[i]; // we send the left part and treat it as a CMD
		lexer[i] = NULL;
		node->left = build_node(lexer);
		lexer[i] = tmp;
		node->right = parser(lexer + i + 1);
	}
	return (node);
}
*/