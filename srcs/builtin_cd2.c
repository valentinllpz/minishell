/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:36:54 by ade-garr          #+#    #+#             */
/*   Updated: 2021/05/21 18:42:31 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_cd_norm(t_shell *shell)
{
	int		ret;
	char	*path;

	ret = chdir(shell->exec[1]);
	if (ret == -1)
	{
		write(1, "cd: ", 4);
		write(1, strerror(errno), ft_strlen_safe(strerror(errno)));
		write(1, "\n", 1);
		shell->return_value = 1;
	}
	if (ret == 0)
	{
		if (env_exists(shell->env, "OLDPWD", 6) == 1)
			change_value_from_env(shell->env,
			get_value_from_env(shell->env, "PWD", 3), "OLDPWD", 6);
		if (env_exists(shell->env, "PWD", 3) == 1)
		{
			path = NULL;
			path = getcwd(path, 0);
			change_value_from_env(shell->env, path, "PWD", 3);
			free(path);
		}
		shell->return_value = 0;
	}
}
