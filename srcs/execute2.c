/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:40:33 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/28 08:22:36 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_do_dup_child(t_shell *shell)
{
	if (close(shell->pipefd[0]) == -1)
		ft_error(shell);
	if (dup2(shell->pipefd[1], 1) == -1)
		ft_error(shell);
	if (close(shell->pipefd[1]) == -1)
		ft_error(shell);
}

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

void	ft_execution(t_shell *shell)
{
	expansion_in_exec_lst(((t_cmd *)shell->tmp_cmd->content)->\
	exec_lst, shell->env, shell->return_value);
	free(shell->envp);
	shell->envp = ft_list_env_to_char(shell->env);
	if (shell->envp == NULL)
		ft_error(shell);
	free(shell->exec);
	shell->exec = ft_list_to_char(((t_cmd *)shell->tmp_cmd->content)->exec_lst);
	if (shell->exec == NULL)
		ft_error(shell);
	if (shell->exec[0] != NULL)
		launch_builtin(shell);
}

void	ft_set_path(t_shell *shell)
{
	char	*env_path;

	env_path = get_value_from_env(shell->env, "PATH", 4);
	if (env_path == NULL || env_path[0] == '\0')
	{
		shell->path = ft_strdup(shell->exec[0]);
		if (shell->path == NULL)
			ft_error(shell);
	}
	else
		ft_set_path2(shell, env_path);
}

void	ft_set_path2(t_shell *shell, char *env_path)
{
	char	**path_split;

	env_path = ft_strdup(env_path);
	if (env_path == NULL)
		ft_error(shell);
	path_split = ft_split(env_path, ':');
	if (path_split == NULL)
	{
		free(env_path);
		ft_error(shell);
	}
	if (ft_set_path3(shell, env_path, path_split) == 1)
	{
		write(2, "minishell: ", 11);
		write(2, shell->exec[0], ft_strlen_safe(shell->exec[0]));
		write(2, ": command not found\n", 20);
		shell->error_flag = 2;
	}
	free(env_path);
	free_charptr(path_split);
}
