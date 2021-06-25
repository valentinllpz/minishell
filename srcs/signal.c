/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:34:55 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/25 14:53:13 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int sig)
{
	if (sig == 2)
		write(1, "\n", 1);
}

void	ft_do_ctrl_c(t_shell *shell)
{
	write(1, "\nminishell$ ", 12);
	free(shell->line);
	shell->line = NULL;
	shell->term->pos_x = 12;
	shell->term->delta = shell->term->pos_x - 1;
	shell->nb_hist = 0;
}

void	ft_do_ctrl_d(t_shell *shell)
{
	int	ret;

	if (ft_strlen_safe(shell->line) == 0)
	{
		ret = shell->return_value;
		free_global_struct(shell);
		write(1, "exit\n", 5);
		exit(ret);
	}
}
