/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:31:09 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/20 12:06:19 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_process_arrow_down(void)
{
	if (g_shell->nb_hist != 0)
	{
		if (g_shell->nb_hist == 1)
		{
			g_shell->nb_hist--;
			ft_unwrite_line();
			free(g_shell->line);
			g_shell->line = g_shell->saved_line;
			ft_write_line();
		}
		else
		{
			g_shell->nb_hist--;
			ft_unwrite_line();
			free(g_shell->line);
			g_shell->line = ft_strdup_safe(ft_get_history());
			if (g_shell->line == NULL)
				ft_error();
			ft_write_line();
		}
	}
}