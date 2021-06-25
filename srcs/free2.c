/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:47:26 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/25 16:56:47 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer(t_token **lexer)
{
	int			i;

	i = 0;
	if (!lexer)
		return ;
	while (lexer[i])
	{
		if (lexer[i]->s)
			free(lexer[i]->s);
		free(lexer[i]);
		i++;
	}
	free(lexer);
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

void	free_global_struct(t_shell *shell)
{
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
	free_global_struct2(shell);
}

void	ft_exit(t_shell *shell)
{
	free_global_struct(shell);
	exit(1);
}
