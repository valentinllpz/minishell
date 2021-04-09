/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:27:23 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/09 15:54:24 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		find_env_var(char *s)
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

void		env_var_expansion(t_list *exec_lst, t_list *env_var)
{
	while (exec_lst)
	{
		if (find_env_var((char *)(exec_lst->content))
		
	}
}