/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:40:33 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/27 09:51:52 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_path(t_shell *shell)
{
	char	*env_path;

	env_path = getenv_path("PATH=", 5, t_list *env);
	if (env_path != NULL)
		env_path = ft_strdup(env_path + 5);
}

void	launch_execution(t_node *node, t_shell *shell)
{
	if (node->type == CMD)
	{
		ft_exec_cmd(node, shell); // a modifier
	}
	else
	{
		launch_execution(node->left, shell);
		launch_execution(node->right, shell);
	}
}

void	ft_execution(t_shell *shell)
{	
	expansion_in_exec_lst(((t_cmd *)shell->tmp_cmd->content)->exec_lst, shell->env);
	free(shell->envp);
	shell->envp = ft_list_to_char(shell->env);
	if (shell->envp == NULL)
		ft_error(shell);
	free(shell->exec);
	shell->exec = ft_list_to_char(((t_cmd *)shell->tmp_cmd->content)->exec_lst);
	if (shell->exec == NULL)
		ft_error(shell);
	if (ft_check_path(shell) == 0)
		ft_set_path(shell);


}