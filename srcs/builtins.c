/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:30:31 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/07 15:16:17 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_builtin(t_shell *shell)
{
	char echo[5];
	char cd[3];
	char pwd[4];
	char export[7];

	ft_strlcpy(echo, "echo", 5);
	ft_strlcpy(cd, "cd", 3);
	ft_strlcpy(pwd, "pwd", 4);
	ft_strlcpy(export, "export", 7);
	if (ft_strncmp(shell->exec[0], echo, 23) == 0)
		return (1);
	if (ft_strncmp(shell->exec[0], cd, 3) == 0)
		return (2);
	if (ft_strncmp(shell->exec[0], pwd, 4) == 0)
		return (3);
	if (ft_strncmp(shell->exec[0], export, 7) == 0)
		return (4);
	return (is_builtin2(shell));
}

int		is_builtin2(t_shell *shell)
{
	char unset[6];
	char env[4];
	char exit[5];

	ft_strlcpy(unset, "unset", 6);
	ft_strlcpy(env, "env", 4);
	ft_strlcpy(exit, "exit", 5);
	if (ft_strncmp(shell->exec[0], unset, 6) == 0)
		return (5);
	if (ft_strncmp(shell->exec[0], env, 4) == 0)
		return (6);
	if (ft_strncmp(shell->exec[0], exit, 5) == 0)
		return (7);
	return (0);
}

void	launch_builtin(t_shell *shell, int i)
{
	// if (i == 1)
	// 	builtin_echo(shell); // à voir avec fonction val
	if (i == 2)
		builtin_cd(shell);
	if (i == 3)
		builtin_pwd(shell);
	if (i == 4)
		builtin_export(shell);
	// if (i == 5)
	// 	builtin_unset(shell);
	// if (i == 6)
	// 	builtin_env(shell);
	// if (i == 7)
	// 	builtin_exit(shell);
}
