/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:28:25 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/15 18:30:00 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_list_env_to_char(t_list *lst)
{
	char	**char_tab;
	int		i;

	i = 0;
	char_tab = malloc(sizeof(char *) * (ft_lstsize_env(lst) + 1));
	if (char_tab == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (is_defined((char *)lst->content) == 1)
		{
			char_tab[i] = ((char *)lst->content);
			i++;
		}
		lst = lst->next;
	}
	char_tab[i] = NULL;
	return (char_tab);
}

void	ft_incr_pos_x(t_shell *shell)
{
	shell->term->pos_x = ((ft_strlen_safe(shell->line) + shell->term->delta)
	% shell->term->nb_col) + 1;
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

void	disable_raw_mode(t_shell *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term->orig_termios) == -1)
		ft_error(shell);
}
