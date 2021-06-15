/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:36:54 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/15 15:08:54 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_cd_norm2(t_shell *shell)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (path == NULL)
	{
		if (errno == 2)
		{
			write(2, "cd: error retrieving current directory: getcwd: ", 48);
			write(2, "cannot access parent directories: ", 34);
			write(2, "No such file or directory\n", 26);
			shell->return_value = 1;
		}
		else
			ft_error(shell);
	}
	else
	{
		if (env_exists(shell->env, "OLDPWD", 6) == 1)
			change_value_from_env(shell->env,
			get_value_from_env(shell->env, "PWD", 3), "OLDPWD", 6);
		if (env_exists(shell->env, "PWD", 3) == 1)
			change_value_from_env(shell->env, path, "PWD", 3);
		free(path);
		shell->return_value = 0;
	}
}

void	builtin_cd_norm(t_shell *shell)
{
	int		ret;
	char	*path;

	ret = chdir(shell->exec[1]);
	if (ret == -1)
	{
		path = strerror(errno);
		write(2, "cd: ", 4);
		write(2, path, ft_strlen_safe(path));
		write(2, "\n", 1);
		shell->return_value = 1;
	}
	if (ret == 0)
		builtin_cd_norm2(shell);
}
