/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:40:47 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/07 16:55:23 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_shell *shell)
{
	t_list	*tmp;

	tmp = shell->env;
	while (tmp != NULL)
	{
		if (is_defined((char *)tmp->content) == 1)
		{
			ft_putstr_fd((char *)tmp->content, 1);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	shell->return_value = 0;
}