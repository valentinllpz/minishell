/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentinll <valentinll@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:27:23 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/10 17:15:10 by valentinll       ###   ########.fr       */
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

t_list		*var_tokenizer(char *var)
{
	char	**split;
	int		i;
	t_list	*lst;

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

void		replace_token(t_list *exec_lst, t_list *env)
{
	int		len;
	char	*var;
	t_list	*tmp;

	len = ft_strlen(((char *)(exec_lst->content))) - 1;//we don't count the $
	while (env)
	{
		if ((var = ft_strnstr(((char *)(env->content) + 1), ((char *)(exec_lst->content)), len)) && var[len] == '=')
		{
			tmp = exec_lst;
			exec_lst = var_tokenizer(var + len + 1);//we send only the part after =
			while (exec_lst)
				exec_lst = exec_lst->next;
			exec_lst->next = tmp;
			return (exec_lst);
		}
		env = env->next;
	}
	return (NULL);
}

void		env_var_expansion(t_list *exec_lst, t_list *rdir_lst, t_list *env)
{	
	while (exec_lst)
	{
		if (is_env_var(((char *)(exec_lst->content))) == 1)
			exec_lst = replace_token(exec_lst, env);
		exec_lst = exec_lst->next;
	}
	// check aussi file dans rdir
}

// add shell lvl
// think about the case where the var is between quotes --> maybe send a struct with the var + a flag if between quotes ?