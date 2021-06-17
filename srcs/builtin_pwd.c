/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:45:56 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/17 11:06:42 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_pwd(t_shell *shell)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (path == NULL)
	{
		if (errno == 2)
		{
			write(2, "pwd: error retrieving current directory: getcwd: ", 49);
			write(2, "cannot access parent directories: ", 34);
			write(2, "No such file or directory\n", 26);
			shell->return_value = 1;
		}
		else
			ft_error(shell);
	}
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	shell->return_value = 0;
}

/*
void	builtin_pwd(t_shell *shell)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (path == NULL)
	{
		if (errno == 2)
		{
			write(2, "pwd: error retrieving current directory: getcwd: ", 49);
			write(2, "cannot access parent directories: ", 34);
			write(2, "No such file or directory\n", 26);
			shell->return_value = 1;
		}
		else
			ft_error(shell);
	}
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	shell->return_value = 0;
}
*/