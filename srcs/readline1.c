/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:26:31 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/24 16:33:00 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_del_char(t_shell *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = shell->line;
	shell->line = malloc(sizeof(char) * (ft_strlen_safe(tmp)));
	if (shell->line == NULL)
	{
		free(tmp);
		ft_error(shell);
	}
	if (tmp != NULL)
	{
		while (tmp[i + 1] != '\0')
		{
			shell->line[i] = tmp[i];
			i++;
		}
	}
	shell->line[i] = '\0';
	free(tmp);
}

void	ft_add_char(char c, t_shell *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = shell->line;
	shell->line = malloc(sizeof(char) * (ft_strlen_safe(tmp) + 2));
	if (shell->line == NULL)
	{
		free(tmp);
		ft_error(shell);
	}
	if (tmp != NULL)
	{
		while (tmp[i] != '\0')
		{
			shell->line[i] = tmp[i];
			i++;
		}
	}
	shell->line[i] = c;
	shell->line[i + 1] = '\0';
	free(tmp);
}

void	ft_analyse_del(t_shell *shell)
{
	if (ft_strlen_safe(shell->line) != 0)
	{
		if ((ft_strlen_safe(shell->line) + shell->term->delta) % shell->term->nb_col == 0
		&& shell->term->pos_x == shell->term->nb_col)
			tputs(shell->term->del_c, 1, ft_putchar);
		else if ((ft_strlen_safe(shell->line) + shell->term->delta) %
		shell->term->nb_col == 0 && shell->term->pos_x == 1)
		{
			tputs(shell->term->line_up, 1, ft_putchar);
			tputs(tgoto(shell->term->end_line, 0, shell->term->nb_col - 1),
			1, ft_putchar);
			tputs(shell->term->del_c, 1, ft_putchar);
		}
		else
		{
			tputs(shell->term->left_c, 1, ft_putchar);
			tputs(shell->term->del_c, 1, ft_putchar);
		}
		ft_del_char(shell);
		shell->term->pos_x = ((ft_strlen_safe(shell->line) + shell->term->delta)
		% shell->term->nb_col) + 1;
	}
}

void	ft_analyse_c(char c, t_shell *shell)
{
	if (ft_isprint_safe(c) == 1)
	{
		write(1, &c, 1);
		ft_add_char(c, shell);
		ft_incr_pos_x(shell);
	}
	if (c == 127)
		ft_analyse_del(shell);
	if (c == 27)
		ft_analyse_escp(shell);
	if (c == 4)
		ft_do_ctrl_d(shell);
	if (c == 3)
		ft_do_ctrl_c(shell);
}

void	ft_readline(t_shell *shell)
{
	char	c;

	while (1)
	{
		enable_raw_mode(shell);
		write(2, "minishell$ ", 11);
		shell->term->pos_x = get_cursor_pos(shell);
		shell->term->delta = shell->term->pos_x - 1;
		shell->nb_hist = 0;
		while (1)
		{
			c = '\0';
			if (read(STDIN_FILENO, &c, 1) == -1)
				ft_error(shell);
			ft_analyse_c(c, shell);
			if (c == 10)
			{
				if (shell->line != NULL && shell->line[0] != '\0')
				{
					ft_add_to_hist(shell);
					break;
				}
				else
				{
						write(1, "\n", 1);
						write(2, "minishell$ ", 11);
						free(shell->line);
						shell->line = NULL;
						shell->term->pos_x = 12;
						shell->term->delta = shell->term->pos_x - 1;
						shell->nb_hist = 0;
				}	
			}
		}
		disable_raw_mode(shell);
		write(1, "\n", 1);
		shell->ast = parser(ft_lexer(shell->line)); // verifier d'abord la valeur de retour de la fonction // $? = 258
		if (shell->ast)
			launch_execution(shell->ast, shell);
		else
			shell->return_value = 2;
		// A MODIFIER + voir si certaines variables ne doivent pas être reset (child_flag / pid_pipe..)
		free_ast(shell->ast);
		shell->ast = NULL;
		if (shell->saved_line != NULL)
		{
			free(shell->saved_line);
			shell->saved_line = NULL;
		}
		free(shell->line);
		shell->line = NULL;
		// A MODIFIER
	}
}
