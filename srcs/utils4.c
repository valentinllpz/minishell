/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 15:40:05 by ade-garr          #+#    #+#             */
/*   Updated: 2021/05/19 13:27:40 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_value_from_env(t_list *env, char *value, char *var, int len)
{
	char	*tmp;
	int		i;

	while (env != NULL)
	{
		if (ft_strncmp(var, (char *)env->content, len) == 0)
		{
			if (((char *)env->content)[len] == '=')
			{
				tmp = (char *)env->content;
				env->content = malloc(sizeof(char) *
				(len + 1 + ft_strlen_safe(value) + 1));
				i = -1;
				while (++i < len + 1)
					((char *)env->content)[i] = tmp[i];
				i = -1;
				while (value != NULL && value[++i] != '\0')
					((char *)env->content)[i + len + 1] = value[i];
				((char *)env->content)[i + len + 1] = '\0';
				free(tmp);
			}
		}
		env = env->next;
	}
}
