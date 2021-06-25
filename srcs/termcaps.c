/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:25:59 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/25 17:44:58 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	param_termcap3(t_shell *shell)
{
	shell->term->end_line = tgetstr("ch", NULL);
	if (shell->term->end_line == NULL)
	{
		write(2, "minishell: end_line tgetstr failed\n", 35);
		ft_exit(shell);
	}
}

void	param_termcap2(t_shell *shell)
{
	shell->term->del_line = tgetstr("dl", NULL);
	if (shell->term->del_line == NULL)
	{
		write(2, "minishell: del_line tgetstr failed\n", 35);
		ft_exit(shell);
	}
	shell->term->left_c = tgetstr("le", NULL);
	if (shell->term->left_c == NULL)
	{
		write(2, "minishell: left_c tgetstr failed\n", 33);
		ft_exit(shell);
	}
	shell->term->nb_col = tgetnum("co");
	if (shell->term->nb_col == -1)
	{
		write(2, "minishell: nb_col tgetnum failed\n", 33);
		ft_exit(shell);
	}
	shell->term->line_up = tgetstr("up", NULL);
	if (shell->term->line_up == NULL)
	{
		write(2, "minishell: line_up tgetstr failed\n", 34);
		ft_exit(shell);
	}
	param_termcap3(shell);
}

void	param_termcap(t_shell *shell)
{
	int		ret;
	char	*env;

	env = getenv("TERM");
	if (env == NULL)
	{
		write(2, "minishell: getenv returned NULL pointer\n", 40);
		ft_exit(shell);
	}
	ret = tgetent(NULL, env);
	if (ret != 1)
	{
		write(2, "minishell: tgetent failed\n", 26);
		ft_exit(shell);
	}
	shell->term->del_c = tgetstr("dc", NULL);
	if (shell->term->del_c == NULL)
	{
		write(2, "minishell: del_c tgetstr failed\n", 32);
		ft_exit(shell);
	}
	param_termcap2(shell);
}

void	enable_raw_mode(t_shell *shell)
{
	struct termios	raw;

	raw = shell->term->orig_termios;
	raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		ft_error(shell);
}
