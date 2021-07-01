/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:31:09 by ade-garr          #+#    #+#             */
/*   Updated: 2021/07/01 19:56:04 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_line_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	ft_readline_loop2(t_shell *shell)
{
	write(1, "\n", 1);
	write(2, "minishell$ ", 11);
	free(shell->line);
	shell->line = NULL;
	shell->term->pos_x = 12;
	shell->term->delta = shell->term->pos_x - 1;
	shell->nb_hist = 0;
}

void	ft_readline_loop(t_shell *shell)
{
	char	c;

	while (1)
	{
		c = '\0';
		if (read(STDIN_FILENO, &c, 1) == -1)
			ft_error(shell);
		ft_analyse_c(c, shell);
		if (c == 10)
		{
			if (shell->line != NULL && ft_check_line_spaces(shell->line) == 1)
			{
				ft_add_to_hist(shell);
				break ;
			}
			else
				ft_readline_loop2(shell);
		}
	}
}

void	ft_process_arrow_down(t_shell *shell)
{
	if (shell->nb_hist != 0)
	{
		if (shell->nb_hist == 1)
		{
			shell->nb_hist--;
			ft_unwrite_line(shell);
			free(shell->line);
			shell->line = shell->saved_line;
			shell->saved_line = NULL;
			ft_write_line(shell);
		}
		else
		{
			shell->nb_hist--;
			ft_unwrite_line(shell);
			free(shell->line);
			shell->line = ft_strdup_safe(ft_get_history(shell));
			if (shell->line == NULL)
				ft_error(shell);
			ft_write_line(shell);
		}
	}
}

char	*ft_get_history(t_shell *shell)
{
	t_list	*tmp_lst;
	int		i;

	i = shell->nb_hist;
	tmp_lst = shell->hist;
	while (ft_lstsize(shell->hist) - i > 0)
	{
		tmp_lst = tmp_lst->next;
		i++;
	}
	return ((char *)tmp_lst->content);
}
