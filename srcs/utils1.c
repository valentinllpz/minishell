/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:28:25 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/28 15:21:54 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_incr_pos_x(t_shell *shell)
{
	shell->term->pos_x = ((ft_strlen_safe(shell->line) + 11) % shell->term->nb_col) + 1;
	if (shell->term->pos_x == 1)
		shell->term->pos_x = shell->term->nb_col;
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

void	ft_error_bis(t_shell *shell)
{
	char	*buf;

	buf = strerror(errno);
	write(2, buf, ft_strlen_safe(buf));
	write(2, "\n", 1);
	ft_exit(shell);
}