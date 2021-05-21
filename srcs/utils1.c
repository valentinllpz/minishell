/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:28:25 by ade-garr          #+#    #+#             */
/*   Updated: 2021/05/21 15:09:21 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_incr_pos_x(t_shell *shell)
{
	shell->term->pos_x = ((ft_strlen_safe(shell->line) + 11)
	% shell->term->nb_col) + 1;
	if (shell->term->pos_x == 1)
		shell->term->pos_x = shell->term->nb_col;
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_iscntrl(char c)
{
	if (((int)c >= 0 && (int)c <= 31) || (int)c == 127)
		return (1);
	return (0);
}

void	disable_raw_mode(t_shell *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term->orig_termios) == -1)
		ft_error(shell);
}
