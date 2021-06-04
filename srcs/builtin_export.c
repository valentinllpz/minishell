/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:09:42 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/04 19:50:39 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_var(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) != 1 && str[i] != '_')
		return (1);
	i++;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isalnum(str[i]) != 1 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	write_var(char *str)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 11);
	while (str[i] != '\0' && str[i] != '=')
	{
		write(1, &str[i], 1);
		i++;
	}
	if (str[i] == '=')
	{
		write(1, "=\"", 2);
		while (str[++i] != '\0')
			write(1, &str[i], 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	builtin_export3(t_shell *shell, int len, int i)
{
	char	*str;
	t_list	*new;

	if (env_exists(shell->env, shell->exec[i], len) == 1)
	{
		str = ft_strdup(shell->exec[i]);
		if (str == NULL)
			ft_error(shell);
		change_variable_in_env(shell->env, str, len);
	}
	else
	{
		str = ft_strdup(shell->exec[i]);
		new = ft_lstnew(str);
		if (str == NULL || new == NULL)
		{
			free(str);
			ft_error(shell);
		}
		ft_lstadd_back(&shell->env, new);
	}
}

void	builtin_export2(t_shell *shell)
{
	int		i;
	int		len;

	i = 1;
	while (shell->exec[i] != NULL)
	{
		len = get_len_var(shell->exec[i]);
		if (ft_check_var(shell->exec[i]) == 1)
		{
			write(1, "export: \'", 9);
			write(1, shell->exec[i], ft_strlen(shell->exec[i]));
			write(1, "\': not a valid identifier\n", 26);
		}
		else
			builtin_export3(shell, len, i);
		i++;
	}
}

void	builtin_export(t_shell *shell)
{
	char	**tmp;
	int		i;

	if (shell->exec[1] == NULL)
	{
		tmp = ft_list_to_char(shell->env);
		if (tmp == NULL)
			ft_error(shell);
		ft_sort_tab(tmp);
		i = 0;
		while (tmp[i] != NULL)
		{
			write_var(tmp[i]);
			i++;
		}
		free(tmp);
	}
	else
		builtin_export2(shell);
}
