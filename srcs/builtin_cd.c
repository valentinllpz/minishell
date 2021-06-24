/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:15:22 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/24 21:38:14 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_cd_oldpwd2(t_shell *shell, char *path)
{
	int		ret;
	char	*tmp_path;

	ret = chdir(path);
	if (ret == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, strerror(errno), ft_strlen_safe(strerror(errno)));
		write(2, "\n", 1);
		shell->return_value = 1;
	}
	if (ret == 0)
	{
		write(1, path, ft_strlen_safe(path));
		write(1, "\n", 1);
		tmp_path = ft_strdup(path);
		if (tmp_path == NULL)
			ft_error(shell);
		change_value_from_env(shell->env, \
		get_value_from_env(shell->env, "PWD", 3), "OLDPWD", 6);
		if (env_exists(shell->env, "PWD", 3) == 1)
			change_value_from_env(shell->env, tmp_path, "PWD", 3);
		shell->return_value = 0;
		free(tmp_path);
	}
}

void	builtin_cd_oldpwd(t_shell *shell)
{
	char	*path;

	path = get_value_from_env(shell->env, "OLDPWD", 6);
	if (path == NULL)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		shell->return_value = 1;
	}
	else
	{
		if (path[0] == '\0')
		{
			write(1, "\n", 1);
			shell->return_value = 0;
			change_value_from_env(shell->env, \
			get_value_from_env(shell->env, "PWD", 3), "OLDPWD", 6);
		}
		else
			builtin_cd_oldpwd2(shell, path);
	}
}

void	builtin_cd_home2(t_shell *shell, char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, strerror(errno), ft_strlen_safe(strerror(errno)));
		write(2, "\n", 1);
		shell->return_value = 1;
	}
	if (ret == 0)
	{
		if (env_exists(shell->env, "OLDPWD", 6) == 1)
			change_value_from_env(shell->env, \
			get_value_from_env(shell->env, "PWD", 3), "OLDPWD", 6);
		if (env_exists(shell->env, "PWD", 3) == 1)
			change_value_from_env(shell->env, path, "PWD", 3);
		shell->return_value = 0;
	}
}

void	builtin_cd_home(t_shell *shell)
{
	char	*path;

	path = get_value_from_env(shell->env, "HOME", 4);
	if (path == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		shell->return_value = 1;
	}
	else if (path[0] == '\0')
		shell->return_value = 0;
	else
		builtin_cd_home2(shell, path);
}

void	builtin_cd(t_shell *shell)
{
	if (shell->exec[1] == NULL)
		builtin_cd_home(shell);
	else if (shell->exec[2] != NULL)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		shell->return_value = 1;
	}
	else if (ft_strcmp(shell->exec[1], "-") == 0)
		builtin_cd_oldpwd(shell);
	else
		builtin_cd_norm(shell);
}
