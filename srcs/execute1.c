/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:30:22 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/30 15:42:44 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_do_dup_parent(t_shell *shell)
{
	if (close(shell->pipefd[1]) == -1)
		ft_error(shell);
	if (dup2(shell->pipefd[0], 0) == -1)
		ft_error(shell);
	if (close(shell->pipefd[0]) == -1)
		ft_error(shell);
	shell->tmp_cmd = shell->tmp_cmd->next;
	ft_do_pipes(shell);
}

void	ft_do_dup_child(t_shell *shell)
{
	if (close(shell->pipefd[0]) == -1)
		ft_error(shell);
	if (dup2(shell->pipefd[1], 1) == -1)
		ft_error(shell);
	if (close(shell->pipefd[1]) == -1)
		ft_error(shell);
}

void	ft_do_pipes(t_shell *shell)
{
	int i;

	if (((t_cmd *)shell->tmp_cmd->content)->pipe_flag == 1)
	{
		i = pipe(shell->pipefd);
		if (i == -1)
			ft_error(shell);
		shell->pid_pipe = fork();
		if (shell->pid_pipe == -1)
			ft_error(shell);
		if (shell->pid_pipe == 0)
		{
			shell->child_flag = 1;
			ft_do_dup_child(shell);
		}
		else
			ft_do_dup_parent(shell);
	}
}

void	ft_process_cmd(t_shell *shell)
{
	ft_do_first_pipe(shell);
	if (shell->parent_flag == 0)
	{
		ft_do_pipes(shell);
		ft_do_redirections(shell);
		if (shell->error_flag == 0)
			ft_execution(shell);
	}
	if (shell->parent_flag == 1)
	{
		if (waitpid(shell->pid_pipe, &shell->pipe_status, 0) == -1)
			ft_error(shell);
		shell->return_value = WEXITSTATUS(shell->pipe_status);
	}
	else if (shell->error_flag == 1)
		shell->return_value = 1;
	else
	{
		if (waitpid(shell->pid_exec, &shell->exec_status, 0) == -1)
			ft_error(shell);
		shell->return_value = WEXITSTATUS(shell->exec_status);
	}
	if (shell->child_flag == 1)
		exit(shell->return_value);
}

void	ft_exec_cmd(t_node *node, t_shell *shell)
{
	int oldstdout;
	int oldstdin;

	shell->tmp_cmd = node->cmd_lst;
	oldstdout = dup(1);
	if (oldstdout == -1)
		ft_error(shell);
	oldstdin = dup(0);
	if (oldstdin == -1)
		ft_error(shell);
	ft_process_cmd(shell);
	if (dup2(oldstdout, 1) == -1)
		ft_error(shell);
	if (dup2(oldstdin, 0) == -1)
		ft_error(shell);
	if (close(oldstdout) == -1)
		ft_error(shell);
	if (close(oldstdin) == -1)
		ft_error(shell);
}
