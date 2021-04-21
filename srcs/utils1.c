/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:28:25 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/20 12:07:55 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_incr_pos_x(void)
{
	g_shell->pos_x = ((ft_strlen_safe(g_shell->line) + 2) % g_shell->nb_col) + 1;
	if (g_shell->pos_x == 1)
		g_shell->pos_x = g_shell->nb_col;
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_iscntrl(char c)
{
	if (((int)c >= 0 && (int)c <= 31) || (int)c == 127)
		return (1);
	return (0);
}

void	ft_lstclear_env(t_list **lst)
{
	t_list	*t;

	if (!lst)
		return ;
	while ((*lst))
	{
		t = *lst;
		*lst = (*lst)->next;
		free(t);
	}
}

void	ft_error_bis(void)
{
	printf("%s\n", strerror(errno));
	ft_exit();
}