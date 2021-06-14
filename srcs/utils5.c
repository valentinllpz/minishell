/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:15:49 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/14 14:14:48 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_shlvl(t_shell *shell)
{
	if env_exists(shell->env, "SHLVL", 5)
	{
		
	}
}

void	change_variable_in_env(t_list *env, char *str, int len)
{
	char *tmp;

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
	return(i);
}