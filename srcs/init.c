/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:53:56 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/25 17:54:20 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell(void)
{
	t_shell	*shell;
	char	*buf;

	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
	{
		write(2, "minishell: ", 11);
		buf = strerror(errno);
		write(2, buf, ft_strlen_safe(buf));
		write(2, "\n", 1);
		exit(1);
	}
	shell->term = ft_calloc(1, sizeof(t_term));
	if (shell->term == NULL)
	{
		free(shell);
		write(2, "minishell: ", 11);
		buf = strerror(errno);
		write(2, buf, ft_strlen_safe(buf));
		write(2, "\n", 1);
		exit(1);
	}
	shell->term->pos_x = 12;
	if (tcgetattr(STDIN_FILENO, &shell->term->orig_termios) == -1)
		ft_error(shell);
	shell->term->flag_termios = 1;
	return (shell);
}
