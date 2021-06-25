/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:58:29 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/25 17:52:27 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_list_env(char **env, t_shell *shell)
{
	int		i;
	t_list	*tmp;
	char	*tmp_char;

	i = 0;
	while (env[i] != NULL)
	{
		tmp_char = ft_strdup(env[i]);
		if (tmp_char == NULL)
			ft_error(shell);
		tmp = ft_lstnew(tmp_char);
		if (tmp == NULL)
		{
			free(tmp_char);
			ft_error(shell);
		}
		ft_lstadd_back(&shell->env, tmp);
		i++;
	}
}

char	**ft_list_env_to_char(t_list *lst)
{
	char	**char_tab;
	int		i;

	i = 0;
	char_tab = malloc(sizeof(char *) * (ft_lstsize_env(lst) + 1));
	if (char_tab == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (is_defined((char *)lst->content) == 1)
		{
			char_tab[i] = ((char *)lst->content);
			i++;
		}
		lst = lst->next;
	}
	char_tab[i] = NULL;
	return (char_tab);
}

int	env_exists(t_list *env, char *var, int len)
{
	while (env != NULL)
	{
		if (ft_strncmp(var, (char *)env->content, len) == 0)
		{
			if (((char *)env->content)[len] == '=' ||
			((char *)env->content)[len] == '\0')
				return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*get_value_from_env(t_list *env, char *var, int len)
{
	while (env != NULL)
	{
		if (ft_strncmp(var, (char *)env->content, len) == 0)
		{
			if (((char *)env->content)[len] == '=')
				return ((char *)env->content + len + 1);
		}
		env = env->next;
	}
	return (NULL);
}

int	ft_lstsize_env(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (is_defined((char *)lst->content) == 1)
			i++;
		lst = lst->next;
	}
	return (i);
}
