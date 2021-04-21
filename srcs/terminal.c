/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:25:59 by ade-garr          #+#    #+#             */
/*   Updated: 2021/03/27 16:12:37 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	param_termcap3()
{
	g_shell->end_line = tgetstr("ch", NULL);
	if (g_shell->end_line == NULL)
	{
		printf("end_line tgetstr failed\r\n");
		ft_exit();
	}
}

void	param_termcap2()
{
	g_shell->del_line = tgetstr("dl", NULL);
	if (g_shell->del_line == NULL)
	{
		printf("del_line tgetstr failed\r\n");
		ft_exit();
	}
	g_shell->left_c = tgetstr("le", NULL);
	if (g_shell->left_c == NULL)
	{
		printf("left_c tgetstr failed\r\n");
		ft_exit();
	}
	g_shell->nb_col = tgetnum("co");
	if (g_shell->nb_col == -1)
	{
		printf("nb_col tgetnum failed\r\n");
		ft_exit();
	}
	g_shell->line_up = tgetstr("up", NULL);
	if (g_shell->line_up == NULL)
	{
		printf("line_up tgetstr failed\r\n");
		ft_exit();
	}
	param_termcap3();
}

void	param_termcap()
{
	int		ret;
	char	*env;

	env = getenv("TERM");
	if (env == NULL)
	{
		printf("getenv returned NULL pointer\r\n");
		ft_exit();
	}
	ret = tgetent(NULL, getenv("TERM"));
	if (ret != 1)
	{
		printf("tgetent failed \r\n");
		ft_exit();
	}
	g_shell->del_c = tgetstr("dc", NULL);
	if (g_shell->del_c == NULL)
	{
		printf("del_c tgetstr failed\r\n");
		ft_exit();
	}
	param_termcap2();
}

void	enable_raw_mode()
{
	struct termios raw;
	
	if (tcgetattr(STDIN_FILENO, &g_shell->orig_termios) == -1)
		ft_error_bis();
	raw = g_shell->orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		ft_error_bis();
	g_shell->flag_termios = 1;
}