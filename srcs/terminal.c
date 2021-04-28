/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:25:59 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/28 15:21:52 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	param_termcap3(t_shell *shell)
{
	shell->term->end_line = tgetstr("ch", NULL);
	if (shell->term->end_line == NULL)
	{
		write(2, "end_line tgetstr failed\r\n", 25);
		ft_exit(shell);
	}
}

void	param_termcap2(t_shell *shell)
{
	shell->term->del_line = tgetstr("dl", NULL);
	if (shell->term->del_line == NULL)
	{
		write(2, "del_line tgetstr failed\r\n", 25);
		ft_exit(shell);
	}
	shell->term->left_c = tgetstr("le", NULL);
	if (shell->term->left_c == NULL)
	{
		printf("left_c tgetstr failed\r\n");
		ft_exit(shell);
	}
	shell->term->nb_col = tgetnum("co");
	if (shell->term->nb_col == -1)
	{
		write(2, "nb_col tgetnum failed\r\n", 23);
		ft_exit(shell);
	}
	shell->term->line_up = tgetstr("up", NULL);
	if (shell->term->line_up == NULL)
	{
		write(2, "line_up tgetstr failed\r\n", 24);
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
		write(2, "getenv returned NULL pointer\r\n", 30);
		ft_exit(shell);
	}
	ret = tgetent(NULL, env);
	if (ret != 1)
	{
		write(2, "tgetent failed \r\n", 17);
		ft_exit(shell);
	}
	shell->term->del_c = tgetstr("dc", NULL);
	if (shell->term->del_c == NULL)
	{
		write(2, "del_c tgetstr failed\r\n", 22);
		ft_exit(shell);
	}
	param_termcap2(shell);
}

void	enable_raw_mode(t_shell *shell)
{
	struct termios raw;
	
	if (tcgetattr(STDIN_FILENO, &shell->term->orig_termios) == -1)
		ft_error_bis(shell);
	raw = shell->term->orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		ft_error_bis(shell);
	shell->term->flag_termios = 1;
}