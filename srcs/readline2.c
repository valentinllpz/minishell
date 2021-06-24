/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 16:54:54 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/24 20:36:31 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_to_hist(t_shell *shell)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp_str = ft_strdup_safe(shell->line);
	if (tmp_str == NULL)
		ft_error(shell);
	tmp = ft_lstnew(tmp_str);
	if (tmp == NULL)
	{
		free(tmp_str);
		ft_error(shell);
	}
	ft_lstadd_back(&shell->hist, tmp);
}

void	ft_unwrite_line(t_shell *shell)
{
	int	i;

	i = 0;
	while ((ft_strlen_safe(shell->line) - i) != 0)
	{
		if (((ft_strlen_safe(shell->line) - i) + shell->term->delta) % \
		shell->term->nb_col == 0 && shell->term->pos_x == shell->term->nb_col)
			tputs(shell->term->del_c, 1, ft_putchar);
		else if (((ft_strlen_safe(shell->line) - i) + shell->term->delta) \
		% shell->term->nb_col == 0 && shell->term->pos_x == 1)
		{
			tputs(shell->term->line_up, 1, ft_putchar);
			tputs(tgoto(shell->term->end_line, 0, shell->term->nb_col - 1), \
			1, ft_putchar);
			tputs(shell->term->del_c, 1, ft_putchar);
		}
		else
		{
			tputs(shell->term->left_c, 1, ft_putchar);
			tputs(shell->term->del_c, 1, ft_putchar);
		}
		i++;
		shell->term->pos_x = (((ft_strlen_safe(shell->line) - i) + \
		shell->term->delta) % shell->term->nb_col) + 1;
	}
}

void	ft_write_line(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->line != NULL && shell->line[i] != '\0')
	{
		write(1, &shell->line[i], 1);
		i++;
	}
	ft_incr_pos_x(shell);
}

void	ft_process_arrow_up(t_shell *shell)
{
	if (shell->nb_hist < ft_lstsize(shell->hist))
	{
		if (shell->nb_hist == 0)
		{
			shell->saved_line = shell->line;
			shell->nb_hist++;
			ft_unwrite_line(shell);
			shell->line = ft_strdup_safe(ft_get_history(shell));
			if (shell->line == NULL)
				ft_error(shell);
			ft_write_line(shell);
		}
		else
		{
			shell->nb_hist++;
			ft_unwrite_line(shell);
			free(shell->line);
			shell->line = ft_strdup_safe(ft_get_history(shell));
			if (shell->line == NULL)
				ft_error(shell);
			ft_write_line(shell);
		}
	}
}

void	ft_analyse_escp(t_shell *shell)
{
	char	buf[4];

	ft_bzero(buf, 4);
	if (read(STDIN_FILENO, buf, 3) == -1)
		ft_error(shell);
	if (buf[0] == '[' && buf[1] == 'A' && buf[2] == '\0')
		ft_process_arrow_up(shell);
	if (buf[0] == '[' && buf[1] == 'B' && buf[2] == '\0')
		ft_process_arrow_down(shell);
}
