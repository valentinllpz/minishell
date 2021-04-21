/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:58:56 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/20 12:08:03 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_global_struct(void) // A MODIFIER, COMPLETER
{
	if (g_shell->env != NULL)
		ft_lstclear_env(&g_shell->env);
	if (g_shell->line != NULL)
	{
		free(g_shell->line);
		g_shell->line = NULL;
	}
	/// FREE CMD ET DIR
	if (g_shell->flag_termios == 1)
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell->orig_termios) == -1)
			printf("%s\r\n", strerror(errno));
	}
	free(g_shell);
	g_shell = NULL;
}

void	ft_do_ctrl_d(void)
{
	int	ret;

	if (ft_strlen_safe(g_shell->line) == 0)
	{
		ret = g_shell->return_value;
		free_global_struct();
		printf("exit\r\n");
		exit(ret);
	}
}

void	ft_error(void)
{
	printf("%s\r\n", strerror(errno));
	ft_exit();
}

char	*ft_get_history(void)
{
	t_list	*tmp_lst;
	int		i;

	i = g_shell->nb_hist;
	tmp_lst = g_shell->hist;
	while (ft_lstsize(g_shell->hist) - i > 0)
	{
		tmp_lst = tmp_lst->next;
		i++;
	}
	return ((char *)tmp_lst->content);
}