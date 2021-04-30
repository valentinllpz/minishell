/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:47:23 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/30 15:56:23 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execution2(t_shell *shell)
{
	int	ret;

	if (shell->error_flag == 0)
	{
		if (shell->child_flag == 0)
			shell->pid_exec = fork();
		if (shell->pid_exec == -1)
			ft_error(shell);
		if (shell->pid_exec == 0)
		{
			ret = execve(shell->path, shell->exec, shell->envp);
			if (ret == -1)
				ft_error(shell);
		}
	}
}

void	ft_do_first_pipe(t_shell *shell)
{
	if (((t_cmd *)shell->tmp_cmd->content)->pipe_flag == 1)
	{
		shell->pid_pipe = fork();
		if (shell->pid_pipe == -1)
			ft_error(shell);
		if (shell->pid_pipe == 0)
			shell->child_flag = 1;
		else
			shell->parent_flag = 1;
	}
}
