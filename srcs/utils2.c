/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:58:56 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/22 09:39:37 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_global_struct(t_shell *shell) // A MODIFIER, COMPLETER
{
	char	*buf;

	if (shell->env != NULL)
		ft_lstclear_env(&shell->env);
	if (shell->line != NULL)
	{
		free(shell->line);
		shell->line = NULL;
	}
	/// FREE CMD ET DIR
	if (shell->flag_termios == 1)
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->orig_termios) == -1)
		{
			buf = strerror(errno);
			write(2, buf, ft_strlen_safe(buf));
			write(2, "\r\n", 2);
		}
	}
	free(shell);
}

void	ft_do_ctrl_d(t_shell *shell)
{
	int	ret;

	if (ft_strlen_safe(shell->line) == 0)
	{
		ret = shell->return_value;
		free_global_struct(shell);
		write(1, "exit\r\n", 6);
		exit(ret);
	}
}

void	ft_error(t_shell *shell)
{
	char	*buf;

	buf = strerror(errno);
	write(2, buf, ft_strlen_safe(buf));
	write(2, "\r\n", 2);
	ft_exit(shell);
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