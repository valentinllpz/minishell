/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:53:56 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/28 08:30:40 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell2(t_shell *shell)
{
	char	*buf;

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
}

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
	init_shell2(shell);
	return (shell);
}
