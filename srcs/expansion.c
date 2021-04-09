/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:27:23 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/09 18:24:16 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_env_var(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && !is_escaped('$', s, i))
			return (1);
		i++;
	}
	return (0);
}

// check aussi file dans rdir

t_list		*var_tokenizer(char *var)
{
	char	**split;
	int		i;
	t_list	*lst;

	if (var[0] == '\'' || var[0] == '\"')
		return (ft_lstnew(ft_strdup(var)));
	split = ft_split(var, ' ');
	while (split[i])
	{
		lst = ft_lstnew(split[i]);
		lst = lst->next;
		i++;
	}
	free(split);
	return (lst);
}

void		replace_token(t_list **exec_lst, t_list *env)
{
	int		len;
	char	*var;

	len = ft_strlen(((char *)((*exec_lst)->content))) - 1;//we don't count the $
	while (env)
	{
		if ((var = ft_strnstr(((char *)(env->content) + 1), ((char *)((*exec_lst)->content)), len)))
		{
			if (var[len] == '=')
				(*exec_lst)->content = ;
		}

	}
}

void		env_var_expansion(t_list *exec_lst, t_list *rdir_lst, t_list *env)
{
	char	*needle;
	
	while (exec_lst)
	{
		if (is_env_var((char *)(exec_lst->content))
		{
			
		}
	}
	while (rdir_lst)
	{
		
	}
}