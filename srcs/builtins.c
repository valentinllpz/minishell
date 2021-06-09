/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:30:31 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/09 12:05:35 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_builtin(t_shell *shell)
{
	if (ft_strncmp(shell->exec[0], "echo", 5) == 0) // mettre strcmp;
		return (1);
	else if (ft_strncmp(shell->exec[0], "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(shell->exec[0], "pwd", 4) == 0)
		return (3);
	else if (ft_strncmp(shell->exec[0], "export", 7) == 0)
		return (4);
	else if (ft_strncmp(shell->exec[0], "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(shell->exec[0], "env", 4) == 0)
		return (6);
	else if (ft_strncmp(shell->exec[0], "exit", 5) == 0)
		return (7);
	return (0);
}

void	launch_builtin(t_shell *shell, int i) // fusionner avec is builtin
{
	if (i == 1)
		builtin_echo(shell);
	else if (i == 2)
		builtin_cd(shell);
	else if (i == 3)
		builtin_pwd(shell);
	else if (i == 4)
		builtin_export(shell);
	else if (i == 5)
		builtin_unset(shell);
	else if (i == 6)
		builtin_env(shell);
	else if (i == 7)
		builtin_exit(shell);
}
