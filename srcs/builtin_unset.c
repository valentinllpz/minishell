/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:52:27 by ade-garr          #+#    #+#             */
/*   Updated: 2021/07/05 16:41:50 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_var2(t_shell *shell, int i)
{
	t_list	*tmp;
	t_list	*tmp_bis;

	tmp = shell->env;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (ft_strncmp((char *)tmp->next->content, shell->exec[i], \
		ft_strlen_safe(shell->exec[i])) == 0)
		{
			if (((char *)tmp->next->content)[ft_strlen_safe(shell->exec[i])]
			== '=' || ((char *)tmp->next->content)
			[ft_strlen_safe(shell->exec[i])] == '\0')
			{
				tmp_bis = tmp->next;
				free(tmp->next->content);
				tmp->next = tmp->next->next;
				free(tmp_bis);
			}
		}
		tmp = tmp->next;
	}
}

void	unset_var(t_shell *shell, int i)
{
	t_list	*tmp;

	if (shell->env != NULL && ft_strncmp((char *)shell->env->content, \
	shell->exec[i], ft_strlen_safe(shell->exec[i])) == 0)
	{
		if (((char *)shell->env->content)[ft_strlen_safe(shell->exec[i])]
		== '=' || ((char *)shell->env->content)
		[ft_strlen_safe(shell->exec[i])] == '\0')
		{
			tmp = shell->env;
			shell->env = shell->env->next;
			free(tmp->content);
			free(tmp);
		}
	}
	unset_var2(shell, i);
}

int	ft_check_var_all(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) != 1 && str[i] != '_')
		return (1);
	i++;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) != 1 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_unset(t_shell *shell)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (shell->exec[i] != NULL)
	{
		if (ft_check_var_all(shell->exec[i]) == 1)
		{
			write(2, "minishell: unset: \'", 19);
			write(2, shell->exec[i], ft_strlen(shell->exec[i]));
			write(2, "\': not a valid identifier\n", 26);
			flag = 1;
		}
		else if (env_exists(shell->env, shell->exec[i], \
		ft_strlen(shell->exec[i])) == 1)
			unset_var(shell, i);
		i++;
	}
	if (flag == 1)
		shell->return_value = 1;
	else
		shell->return_value = 0;
}
