/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:33:39 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/17 17:13:12 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_dollar_sign(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && !is_escaped(s, i))
			return (1);
		i++;
	}
	return (0);
}

void		replace_elem(t_token **content, t_list *elem)
{
	int			i;
	int			flag;
	t_list		*lst;

	i = 0;
	flag = 0;
	lst = NULL;
	while (content[i])
	{
		if (flag == 0)
		{
			free(elem->content);
			elem->content = ft_strdup(content[i]->s);
			flag = 1;
		}
		else
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(content[i]->s)));
		i++;
	}
	ft_lstadd_back(&lst, elem->next);
	elem->next = lst;
	free_lexer(content);
}

void	expansion_in_exec_lst(t_list *exec_lst, t_list *env, int return_value)
{
	while (exec_lst)
	{
		if (check_dollar_sign(exec_lst->content))
		{
				exec_lst->content = expand_content(exec_lst->content, env, return_value);
				if (ft_strcmp(exec_lst->content, "") != 0)
					replace_elem(ft_lexer(exec_lst->content), exec_lst);
				else
				{
					free(exec_lst->content);
					exec_lst->content = NULL;
				}
		}
		if (exec_lst->content)
			exec_lst->content = str_cleanup(exec_lst->content);
		exec_lst = exec_lst->next;
	}
}

int		is_ambiguous_redirect(char *s) // call la fonction avant le expand content en cas d'ambiguous redirect pour afficher le token original et pas le remplacant 
{
	int			i;
	t_token		**tmp;

	i = 0;
	if (!s || s[0] == '\0')
		return (1);
	tmp = ft_lexer(s);
	while (tmp[i])
		i++;
	free_lexer(tmp);
	if (i > 1)
		return (1);
	return (0);
}

void	expansion_in_rdir_lst(t_list *rdir_lst, t_list *env, int return_value)
{
	while (rdir_lst)
	{
		if (check_dollar_sign(((t_rdir *)(rdir_lst->content))->file))
		{
			((t_rdir *)(rdir_lst->content))->file =
			expand_content(((t_rdir *)(rdir_lst->content))->file, env, return_value);
			if (is_ambiguous_redirect(((t_rdir *)(rdir_lst->content))->file))
				((t_rdir *)(rdir_lst->content))->flag = 0;
		}
		((t_rdir *)(rdir_lst->content))->file = str_cleanup(((t_rdir *)(rdir_lst->content))->file);
		rdir_lst = rdir_lst->next;
	}
}
