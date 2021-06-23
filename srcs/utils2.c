/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:58:56 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/23 16:06:02 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_list_to_char(t_list *lst)
{
	char	**char_tab;
	int		i;

	i = 0;
	char_tab = malloc(sizeof(char *) * (ft_lstsize_exec(lst) + 1));
	if (char_tab == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->content != NULL)
		{
			char_tab[i] = ((char *)lst->content);
			i++;		
		}
		lst = lst->next;
	}
	char_tab[i] = NULL;
	return (char_tab);
}

void	free_global_struct(t_shell *shell) // A MODIFIER, COMPLETER
{
	char	*buf;

	if (shell->env != NULL)
		ft_lstclear(&shell->env, free);
	if (shell->envp != NULL)
	{
		free(shell->envp);
		shell->envp = NULL;
	}
	if (shell->exec != NULL)
	{
		free(shell->exec);
		shell->exec = NULL;
	}
	if (shell->path != NULL)
	{
		free(shell->path);
		shell->path = NULL;
	}
	free_ast(shell->ast);
	if (shell->line != NULL)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->term != NULL && shell->term->flag_termios == 1)
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term->orig_termios)
		== -1)
		{
			buf = strerror(errno);
			write(2, buf, ft_strlen_safe(buf));
			write(2, "\n", 1);
		}
	}
	if (shell->term != NULL)
	{
		free(shell->term);
		shell->term = NULL;
	}
	if (shell->saved_line != NULL)
	{
		free(shell->saved_line);
		shell->saved_line = NULL;
	}
	if (shell->hist != NULL)
		ft_lstclear(&shell->hist, free);
	free(shell);
}

void	ft_do_ctrl_d(t_shell *shell)
{
	int	ret;

	if (ft_strlen_safe(shell->line) == 0)
	{
		ret = shell->return_value;
		free_global_struct(shell);
		write(1, "exit\n", 5);
		exit(ret);
	}
}

void	ft_error(t_shell *shell)
{
	char	*buf;

	buf = strerror(errno);
	write(2, buf, ft_strlen_safe(buf));
	write(2, "\n", 1);
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
