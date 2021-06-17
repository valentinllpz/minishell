/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:47:23 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/17 17:06:36 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_return_value(t_shell *shell)
{
	if (shell->parent_flag == 1)
	{
		if (waitpid(shell->pid_pipe, &shell->pipe_status, 0) == -1)
			ft_error(shell);
		shell->return_value = WEXITSTATUS(shell->pipe_status);
	}
	else if (shell->error_flag == 1)
		shell->return_value = 1;
	else if (shell->error_flag == 2)
		shell->return_value = 127;
	else
	{
		if (((t_cmd *)shell->tmp_cmd->content)->exec_lst == NULL)
			shell->return_value = 0;
		if (shell->pid_exec != 0)
		{
			if (waitpid(shell->pid_exec, &shell->exec_status, 0) == -1)
				ft_error(shell);
			if (WIFSIGNALED(shell->exec_status) == 1)
			{
				shell->return_value = 128 + WTERMSIG(shell->exec_status);
				if (WTERMSIG(shell->exec_status) == 3)
					write(1, "Quit: 3\n", 8);
			}
			else
				shell->return_value = WEXITSTATUS(shell->exec_status);
		}
		close(0);
		if (shell->pid_pipe != 0)
		{
			while (waitpid(0, &shell->pipe_status, 0) != -1)
				;
		}
	}
	if (shell->child_flag == 1)
	{
		free(shell->path);
		shell->path = NULL;
		exit(shell->return_value);
	}
}

void	ft_execution2(t_shell *shell)
{
	int		ret;

	if (shell->error_flag == 0)
	{
		shell->pid_exec = fork();
		if (shell->pid_exec == -1)
			ft_error(shell);
		if (shell->pid_exec == 0)
		{			
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			ret = execve(shell->path, shell->exec, shell->envp);
			if (ret == -1)
			{
				if (errno == 13)
				{
					write(2, "minishell: ", 11);
					write(2, shell->path, ft_strlen(shell->path));
					write(2, ": ", 2);
					write(2, strerror(errno), ft_strlen(strerror(errno)));
					write(2, "\n", 1);
					exit(126);
				}
				else if (errno == 2)
				{
					write(2, "minishell: ", 11);
					write(2, shell->path, ft_strlen(shell->path));
					write(2, ": ", 2);
					write(2, strerror(errno), ft_strlen(strerror(errno)));
					write(2, "\n", 1);
					exit(127);
				}
				else
					exit(1);
				//ft_error(shell); A VOIR SI A REMETTRE POUR LEAKS
			}
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
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			shell->child_flag = 1;
		}
		else
			shell->parent_flag = 1;
	}
}
