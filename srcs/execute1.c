/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:30:22 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/28 08:22:43 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_execution(t_node *node, t_shell *shell)
{
	if (node->type == CMD)
	{
		free(shell->path);
		shell->path = NULL;
		shell->exec_status = 0;
		shell->pipe_status = 0;
		shell->pid_pipe = 0;
		shell->pid_exec = 0;
		shell->error_flag = 0;
		shell->parent_flag = 0;
		shell->child_flag = 0;
		ft_exec_cmd(node, shell);
	}
	else
	{
		launch_execution(node->left, shell);
		launch_execution(node->right, shell);
	}
}

void	ft_exec_cmd(t_node *node, t_shell *shell)
{
	shell->tmp_cmd = node->cmd_lst;
	shell->tmp_stdout = dup(1);
	if (shell->tmp_stdout == -1)
		ft_error(shell);
	shell->tmp_stdin = dup(0);
	if (shell->tmp_stdin == -1)
		ft_error(shell);
	ft_process_cmd(shell);
	if (dup2(shell->tmp_stdout, 1) == -1)
		ft_error(shell);
	if (dup2(shell->tmp_stdin, 0) == -1)
		ft_error(shell);
	if (close(shell->tmp_stdout) == -1)
		ft_error(shell);
	if (close(shell->tmp_stdin) == -1)
		ft_error(shell);
}

void	ft_process_cmd(t_shell *shell)
{
	ft_do_first_pipe(shell);
	if (shell->parent_flag == 0)
	{
		ft_do_pipes(shell);
		ft_do_redirections(shell);
		if (shell->error_flag == 0
			&& ((t_cmd *)shell->tmp_cmd->content)->exec_lst != NULL)
			ft_execution(shell);
	}
	get_return_value(shell);
}

void	ft_do_first_pipe(t_shell *shell)
{
	if (((t_cmd *)shell->tmp_cmd->content)->pipe_flag == 1)
	{
		shell->pid_pipe = fork();
		if (shell->pid_pipe == -1)
			ft_error(shell);
		if (shell->pid_pipe == 0)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			shell->child_flag = 1;
		}
		else
			shell->parent_flag = 1;
	}
}

void	ft_do_pipes(t_shell *shell)
{
	int	i;

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
