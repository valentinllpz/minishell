/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:47:23 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/28 08:22:40 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_set_path3(t_shell *shell, char *env_path, char **path_split)
{
	int			i;
	char		*tmp;
	struct stat	buf;

	i = 0;
	while (path_split[i] != NULL)
	{
		tmp = ft_strjoin(path_split[i], "/");
		shell->path = ft_strjoin(tmp, shell->exec[0]);
		if (tmp == NULL || shell->path == NULL)
		{
			free(tmp);
			free(env_path);
			free_charptr(path_split);
			ft_error(shell);
		}
		free(tmp);
		if (stat(shell->path, &buf) == 0 && S_ISREG(buf.st_mode) == 1)
			return (0);
		free(shell->path);
		shell->path = NULL;
		i++;
	}
	return (1);
}

void	get_return_value2(t_shell *shell)
{
	if (((t_cmd *)shell->tmp_cmd->content)->exec_lst == NULL \
	|| shell->exec[0] == NULL)
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
		get_return_value2(shell);
	if (shell->child_flag == 1)
	{
		free(shell->path);
		shell->path = NULL;
		exit(shell->return_value);
	}
}

void	ft_execution2_errno(t_shell *shell)
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
		ft_error(shell);
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
				ft_execution2_errno(shell);
		}
	}
}
