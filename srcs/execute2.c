/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:40:33 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/07 14:14:49 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_set_path3(t_shell *shell, char *env_path, char **path_split)
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
		i++;
	}
	return (1);
}

void	ft_set_path2(t_shell *shell, char *env_path)
{
	char	**path_split;

	env_path = ft_strdup(env_path + 5);
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
		write(2, shell->exec[0], ft_strlen_safe(shell->exec[0]));
		write(2, ": command not found\n", 20);
		shell->error_flag = 1;
	}
	free(env_path);
	free_charptr(path_split);
}

void	ft_set_path(t_shell *shell)
{
	char	*env_path;

	env_path = getenv_path("PATH=", 5, shell->env);
	if (env_path == NULL)
	{
		write(2, shell->exec[0], ft_strlen_safe(shell->exec[0]));
		write(2, ": command not found\n", 20);
		shell->error_flag = 1;
	}
	else
		ft_set_path2(shell, env_path);
}

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

void	ft_execution(t_shell *shell)
{
	expansion_in_exec_lst(((t_cmd *)shell->tmp_cmd->content)->
	exec_lst, shell->env);
	free(shell->envp);
	shell->envp = ft_list_env_to_char(shell->env);
	if (shell->envp == NULL)
		ft_error(shell);
	free(shell->exec);
	shell->exec = ft_list_to_char(((t_cmd *)shell->tmp_cmd->content)->exec_lst);
	if (shell->exec == NULL)
		ft_error(shell);
	if (is_builtin(shell) > 0)
		launch_builtin(shell, is_builtin(shell));
	else
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
}
