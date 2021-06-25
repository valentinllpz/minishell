/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:06:19 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/25 17:51:11 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	change_variable_in_env(t_list *env, char *str, int len)
{
	char	*tmp;

	while (env != NULL)
	{
		if (ft_strncmp(str, (char *)env->content, len) == 0)
		{
			if (((char *)env->content)[len] == '=' ||
			((char *)env->content)[len] == '\0')
			{
				tmp = (char *)env->content;
				env->content = str;
				free(tmp);
			}
		}
		env = env->next;
	}
}

int	get_len_var(char *s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && s[i] != '=')
		i++;
	return (i);
}

int	ft_check_path(t_shell *shell)
{
	char	*buf;
	int		i;

	i = 0;
	buf = shell->exec[0];
	if (buf != NULL)
	{
		while (buf[i] != '\0')
		{
			if (buf[i] == '/')
				return (1);
			i++;
		}
	}
	return (0);
}
