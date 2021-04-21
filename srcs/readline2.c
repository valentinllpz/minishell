/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 16:54:54 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/20 12:07:41 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_to_hist(void)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp_str = ft_strdup_safe(g_shell->line);
	if (tmp_str == NULL)
		ft_error();
	tmp = ft_lstnew(tmp_str);
	if (tmp == NULL)
	{
		free(tmp_str);
		ft_error();
	}
	ft_lstadd_back(&g_shell->hist, tmp);
}

void	ft_unwrite_line(void)
{
	int	i;

	i = 0;
	while ((ft_strlen_safe(g_shell->line) - i) != 0)
	{
		if (((ft_strlen_safe(g_shell->line) - i) + 2) % g_shell->nb_col == 0
		&& g_shell->pos_x == g_shell->nb_col)
			tputs(g_shell->del_c, 1, ft_putchar);
		else if (((ft_strlen_safe(g_shell->line) - i) + 2) % g_shell->nb_col == 0
		&& g_shell->pos_x == 1)
		{
			tputs(g_shell->line_up, 1, ft_putchar);
			tputs(tgoto(g_shell->end_line, 0, g_shell->nb_col - 1),
			1, ft_putchar);
			tputs(g_shell->del_c, 1, ft_putchar);
		}
		else
		{
			tputs(g_shell->left_c, 1, ft_putchar);
			tputs(g_shell->del_c, 1, ft_putchar);
		}
		i++;
		g_shell->pos_x = (((ft_strlen_safe(g_shell->line) - i) + 2)
		% g_shell->nb_col) + 1;
	}
}

void	ft_write_line(void)
{
	int	i;

	i = 0;
	while (g_shell->line != NULL && g_shell->line[i] != '\0')
	{
		write(1, &g_shell->line[i], 1);
		i++;
	}
	ft_incr_pos_x();
}

void	ft_process_arrow_up(void)
{
	if (g_shell->nb_hist < ft_lstsize(g_shell->hist))
	{
		if (g_shell->nb_hist == 0)
		{
			g_shell->saved_line = g_shell->line;
			g_shell->nb_hist++;
			ft_unwrite_line();
			g_shell->line = ft_strdup_safe(ft_get_history());
			if (g_shell->line == NULL)
				ft_error();
			ft_write_line();
		}
		else
		{
			g_shell->nb_hist++;
			ft_unwrite_line();
			free(g_shell->line);
			g_shell->line = ft_strdup_safe(ft_get_history());
			if (g_shell->line == NULL)
				ft_error();
			ft_write_line();
		}
	}
}

void	ft_analyse_escp(void)
{
	char	buf[4];

	buf[0] = '\0';
	buf[1] = '\0';
	buf[2] = '\0';
	if (read(STDIN_FILENO, buf, 3) == -1)
		ft_error();
	buf[3] = '\0';
	if (buf[0] == '[' && buf[1] == 'A' && buf[2] == '\0')
		ft_process_arrow_up();
	if (buf[0] == '[' && buf[1] == 'B' && buf[2] == '\0')
		ft_process_arrow_down();
}
