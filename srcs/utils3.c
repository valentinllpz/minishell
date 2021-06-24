/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 10:06:54 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/24 20:50:30 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_global_struct2(t_shell *shell)
{
	char	*buf;

	if (shell->term != NULL && shell->term->flag_termios == 1)
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term->orig_termios) \
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

int	env_exists(t_list *env, char *var, int len)
{
	while (env != NULL)
	{
		if (ft_strncmp(var, (char *)env->content, len) == 0)
		{
			if (((char *)env->content)[len] == '=' ||
			((char *)env->content)[len] == '\0')
				return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*get_value_from_env(t_list *env, char *var, int len)
{
	while (env != NULL)
	{
		if (ft_strncmp(var, (char *)env->content, len) == 0)
		{
			if (((char *)env->content)[len] == '=')
				return ((char *)env->content + len + 1);
		}
		env = env->next;
	}
	return (NULL);
}

void	free_charptr(char **ptr)
{
	int	i;

	i = 0;
	if (ptr != NULL)
	{
		while (ptr[i] != NULL)
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
	}
}

int	ft_check_path(t_shell *shell)
{
	char	*buf;
	int		i;

	i = 0;
	buf = shell->exec[0];
	if (buf != NULL)
	{
		while (buf[i] != '\0')
		{
			if (buf[i] == '/')
				return (1);
			i++;
		}
	}
	return (0);
}
