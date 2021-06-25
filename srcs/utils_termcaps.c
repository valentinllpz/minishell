/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:28:25 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/25 17:37:13 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_incr_pos_x(t_shell *shell)
{
	shell->term->pos_x = ((ft_strlen_safe(shell->line) + shell->term->delta) \
	% shell->term->nb_col) + 1;
	if (shell->term->pos_x == 1)
		shell->term->pos_x = shell->term->nb_col;
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	disable_raw_mode(t_shell *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term->orig_termios) == -1)
		ft_error(shell);
}

int	get_cursor_pos(t_shell *shell)
{
	char	buf[100];
	int		ret;
	int		i;

	i = 0;
	if (write(1, "\033[6n", 4) != 4)
		ft_error(shell);
	ret = read(STDIN_FILENO, buf, 99);
	buf[ret] = '\0';
	while (buf[i] != ';')
		i++;
	i++;
	ret = ft_atoi(buf + i);
	return (ret);
}
