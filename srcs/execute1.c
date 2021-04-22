/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:30:22 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/22 09:59:36 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_do_dup_parent(t_shell *shell)
{
	if (close(shell->pipefd[0]) == -1)
		ft_error(shell);
	if (dup2(shell->pipefd[1], 1) == -1)
		ft_error(shell);
	if (close(shell->pipefd[1]) == -1)
		ft_error(shell);
}

void	ft_do_dup_child(t_shell *shell)
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
			shell->child_flag = 1; // à garder ?
			ft_do_dup_child(shell);
		}
		else
			ft_do_dup_parent(shell);
	}
}

void	ft_process_cmd(t_shell *shell)
{
	ft_do_pipes(shell);
	ft_do_redirections(shell);

	// POUR TEST PIPES
	if (shell->error_flag == 0)
	{
		write(1, ((char *)((t_cmd *)shell->tmp_cmd->content)->exec_lst->content), 4);
		write(1, " ", 1);
		write(1, ((char *)((t_cmd *)shell->tmp_cmd->content)->exec_lst->next->content), 3);
		write(1, "\r\n", 2);
	}
	// FIN TEST PIPES
	if (shell->pid_pipe != 0)
		waitpid(shell->pid_pipe, &shell->child_status, 0);
	if (shell->child_flag == 1)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->orig_termios);
		exit(0);
	}
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