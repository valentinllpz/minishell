/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:31:09 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/22 09:55:58 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_process_arrow_down(t_shell *shell)
{
	if (shell->nb_hist != 0)
	{
		if (shell->nb_hist == 1)
		{
			shell->nb_hist--;
			ft_unwrite_line(shell);
			free(shell->line);
			shell->line = shell->saved_line;
			ft_write_line(shell);
		}
		else
		{
			shell->nb_hist--;
			ft_unwrite_line(shell);
			free(shell->line);
			shell->line = ft_strdup_safe(ft_get_history(shell));
			if (shell->line == NULL)
				ft_error(shell);
			ft_write_line(shell);
		}
	}
}