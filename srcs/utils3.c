/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 10:06:54 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/30 16:23:13 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_charptr(char **ptr)
{
	int	i;

	i = 0;
	if (ptr != NULL)
	{
		while (ptr[i] != NULL)
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
	}
}

char	*getenv_path(char *s, int len, t_list *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(s, (char *)env->content, len) == 0)
			return ((char *)env->content);
		env = env->next;
	}
	return (NULL);
}

int		ft_check_path(t_shell *shell)
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
