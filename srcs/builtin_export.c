/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:09:42 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/01 09:47:32 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_export(t_shell *shell)
{
	t_list	*tmp;
	int		i;

	if (shell->exec[1] == NULL)
	{
		tmp = shell->env;
		while (tmp != NULL)
		{
			i = 0;
			write(1, "declare -x ", 11);
			while (((char *)tmp->content)[i] != '\0' && ((char *)tmp->content)[i] != '=')
			{
				write(1, &((char *)tmp->content)[i], 1);
				i++;
			}
			if (((char *)tmp->content)[i] == '=')
			{
				write(1, "=\"", 2);
				while (((char *)tmp->content)[++i] != '\0')
					write(1, &((char *)tmp->content)[i], 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
			tmp = tmp->next;
		}
	}
}
