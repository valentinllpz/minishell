/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 15:40:05 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/04 14:12:50 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sort_tab(char **tb)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tb[i + 1] != NULL)
	{
		if (ft_strncmp(tb[i], tb[i + 1], 1000) > 0)
		{
			tmp = tb[i];
			tb[i] = tb[i + 1];
			tb[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

int		is_defined(char *s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		ft_lstsize_env(t_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		if (is_defined((char *)lst->content) == 1)
			i++;
		lst = lst->next;
	}
	return (i);
}

void	change_value_from_env2(t_list *env, char *value, int len)
{
	char	*tmp;
	int		i;

	tmp = (char *)env->content;
	env->content = malloc(sizeof(char) * (len + 1 + ft_strlen_safe(value) + 1));
	i = -1;
	while (++i < len)
		((char *)env->content)[i] = tmp[i];
	((char *)env->content)[i] = '=';
	i = -1;
	while (value != NULL && value[++i] != '\0')
		((char *)env->content)[i + len + 1] = value[i];
	((char *)env->content)[i + len + 1] = '\0';
	free(tmp);
}

void	change_value_from_env(t_list *env, char *value, char *var, int len)
{
	while (env != NULL)
	{
		if (ft_strncmp(var, (char *)env->content, len) == 0)
		{
			if (((char *)env->content)[len] == '=' ||
			((char *)env->content)[len] == '\0')
				change_value_from_env2(env, value, len);
		}
		env = env->next;
	}
}
