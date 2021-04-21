/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:30:22 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/19 17:10:37 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_do_dup_parent(void)
{
	if (close(g_shell->pipefd[0]) == -1)
		ft_error();
	if (dup2(g_shell->pipefd[1], 1) == -1)
		ft_error();
	if (close(g_shell->pipefd[1]) == -1)
		ft_error();
}

void	ft_do_dup_child(void)
{
	if (close(g_shell->pipefd[1]) == -1)
		ft_error();
	if (dup2(g_shell->pipefd[0], 0) == -1)
		ft_error();
	if (close(g_shell->pipefd[0]) == -1)
		ft_error();
	g_shell->tmp_cmd = g_shell->tmp_cmd->next;
	ft_do_pipes();
}

void	ft_do_pipes(void)
{
	int i;

	if (((t_cmd *)g_shell->tmp_cmd->content)->pipe_flag == 1)
	{
		i = pipe(g_shell->pipefd);
		if (i == -1)
			ft_error();
		g_shell->pid_pipe = fork();
		if (g_shell->pid_pipe == -1)
			ft_error();
		if (g_shell->pid_pipe == 0)
		{
			g_shell->child_flag = 1; // à garder ?
			ft_do_dup_child();
		}
		else
			ft_do_dup_parent();
	}
}

void	ft_process_cmd(void)
{
	ft_do_pipes();
	ft_do_redirections();

	// POUR TEST PIPES
	write(1, ((char *)((t_cmd *)g_shell->tmp_cmd->content)->exec_lst->content), 4);
	write(1, " ", 1);
	write(1, ((char *)((t_cmd *)g_shell->tmp_cmd->content)->exec_lst->next->content), 3);
	write(1, "\r\n", 2);
	// FIN TEST PIPES
	if (g_shell->pid_pipe != 0)
		waitpid(g_shell->pid_pipe, &g_shell->child_status, 0);
	if (g_shell->child_flag == 1)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell->orig_termios);
		exit(0);
	}
}

void	ft_exec_cmd(t_node *node)
{
	int oldstdout;
	int oldstdin;

	g_shell->tmp_cmd = node->cmd_lst;
	oldstdout = dup(1);
	if (oldstdout == -1)
		ft_error();
	oldstdin = dup(0);
	if (oldstdin == -1)
		ft_error();
	ft_process_cmd();
	if (dup2(oldstdout, 1) == -1)
		ft_error();
	if (dup2(oldstdin, 0) == -1)
		ft_error();
	if (close(oldstdout) == -1)
		ft_error();
	if (close(oldstdin) == -1)
		ft_error();
}