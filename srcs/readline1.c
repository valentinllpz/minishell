/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:26:31 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/20 12:07:09 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_del_char(void)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = g_shell->line;
	g_shell->line = malloc(sizeof(char) * (ft_strlen_safe(tmp)));
	if (g_shell->line == NULL)
	{
		free(tmp);
		ft_error();
	}
	if (tmp != NULL)
	{
		while (tmp[i + 1] != '\0')
		{
			g_shell->line[i] = tmp[i];
			i++;
		}
	}
	g_shell->line[i] = '\0';
	free(tmp);
}

void	ft_add_char(char c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = g_shell->line;
	g_shell->line = malloc(sizeof(char) * (ft_strlen_safe(tmp) + 2));
	if (g_shell->line == NULL)
	{
		free(tmp);
		ft_error();
	}
	if (tmp != NULL)
	{
		while (tmp[i] != '\0')
		{
			g_shell->line[i] = tmp[i];
			i++;
		}
	}
	g_shell->line[i] = c;
	g_shell->line[i + 1] = '\0';
	free(tmp);
}

void	ft_analyse_del(void)
{
	if (ft_strlen_safe(g_shell->line) != 0)
	{
		if ((ft_strlen_safe(g_shell->line) + 2) % g_shell->nb_col == 0 && g_shell->pos_x == g_shell->nb_col)
			tputs(g_shell->del_c, 1, ft_putchar);
		else if ((ft_strlen_safe(g_shell->line) + 2) % g_shell->nb_col == 0 && g_shell->pos_x == 1)
		{
			tputs(g_shell->line_up, 1, ft_putchar);
			tputs(tgoto(g_shell->end_line, 0, g_shell->nb_col - 1), 1, ft_putchar);
			tputs(g_shell->del_c, 1, ft_putchar);
		}
		else
		{
			tputs(g_shell->left_c, 1, ft_putchar);
			tputs(g_shell->del_c, 1, ft_putchar);
		}
		ft_del_char();
		g_shell->pos_x = ((ft_strlen_safe(g_shell->line) + 2) % g_shell->nb_col) + 1;
	}
}

void	ft_analyse_c(char c)
{
	if (ft_isprint_safe(c) == 1)
	{
		write(1, &c, 1);
		ft_add_char(c);
		ft_incr_pos_x();
	}
	if (c == 127)
		ft_analyse_del();
	if (c == 27)
		ft_analyse_escp();
	if (c == 4)
		ft_do_ctrl_d();
	// A VIRER
	if (c == 'q')
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell->orig_termios);
		exit(1);
	}
	// A VIRER
}


void	ft_readline(void)
{
	char	c;

	while (1)
	{
		write(2, "$ ", 2);
		g_shell->pos_x = 3;
		g_shell->nb_hist = 0;
		while (1)
		{
			c =  '\0';
			if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
				ft_error();
			ft_analyse_c(c);
			if (c == 13)
				if (g_shell->line != NULL && g_shell->line[0] != '\0')
				{
					ft_add_to_hist();
					break;
				}
		}
		write(2, "\r\n", 2);
		g_shell->ast = ft_launch_lexer(g_shell->line);
		launch_execution(g_shell->ast);
		// A MODIFIER + voir si certaines variables ne doivent pas être reset (child_flag / pid_pipe..)
		free_ast(g_shell->ast);
		free(g_shell->line);
		g_shell->line = NULL;
		// A MODIFIER
	}
}