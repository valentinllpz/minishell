/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:45:56 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/28 08:45:57 by ade-garr         ###   ########.fr       */
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
			write(2, "minishell: pwd: error retrieving current directory:", 51);
			write(2, " getcwd: cannot access parent directories: ", 43);
			write(2, "No such file or directory\n", 26);
			shell->return_value = 1;
		}
		else
			ft_error(shell);
	}
	else
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		free(path);
		shell->return_value = 0;
	}
}
