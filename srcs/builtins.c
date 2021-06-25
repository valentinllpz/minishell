/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:30:31 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/25 15:11:09 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_bin(t_shell *shell)
{
	if (ft_check_path(shell) == 0)
		ft_set_path(shell);
	else
	{
		shell->path = ft_strdup(shell->exec[0]);
		if (shell->path == NULL)
			ft_error(shell);
	}
	ft_execution2(shell);
}

void	launch_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->exec[0], "echo") == 0)
		builtin_echo(shell);
	else if (ft_strcmp(shell->exec[0], "cd") == 0)
		builtin_cd(shell);
	else if (ft_strcmp(shell->exec[0], "pwd") == 0)
		builtin_pwd(shell);
	else if (ft_strcmp(shell->exec[0], "export") == 0)
		builtin_export(shell);
	else if (ft_strcmp(shell->exec[0], "unset") == 0)
		builtin_unset(shell);
	else if (ft_strcmp(shell->exec[0], "env") == 0)
		builtin_env(shell);
	else if (ft_strcmp(shell->exec[0], "exit") == 0)
		builtin_exit(shell);
	else
		launch_bin(shell);
}
