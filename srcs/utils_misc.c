/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:58:56 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/25 17:49:40 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize_exec(t_list *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		if (lst->content != NULL)
			size++;
		lst = lst->next;
	}
	return (size);
}

char	**ft_list_to_char(t_list *lst)
{
	char	**char_tab;
	int		i;

	i = 0;
	char_tab = malloc(sizeof(char *) * (ft_lstsize_exec(lst) + 1));
	if (char_tab == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->content != NULL)
		{
			char_tab[i] = ((char *)lst->content);
			i++;
		}
		lst = lst->next;
	}
	char_tab[i] = NULL;
	return (char_tab);
}

void	ft_error(t_shell *shell)
{
	char	*buf;

	buf = strerror(errno);
	write(2, buf, ft_strlen_safe(buf));
	write(2, "\n", 1);
	ft_exit(shell);
}

void	add_shlvl(t_shell *shell)
{
	char	*s;
	int		i;

	if (env_exists(shell->env, "SHLVL", 5) == 1)
	{
		s = get_value_from_env(shell->env, "SHLVL", 5);
		if (s != NULL)
		{
			i = ft_atoi(s);
			i = i + 1;
			s = ft_itoa(i);
			if (s == NULL)
				ft_error(shell);
			change_value_from_env(shell->env, s, "SHLVL", 5);
			free(s);
		}
	}
}

void	ft_sort_tab(char **tb)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tb[i + 1] != NULL)
	{
		if (ft_strcmp(tb[i], tb[i + 1]) > 0)
		{
			tmp = tb[i];
			tb[i] = tb[i + 1];
			tb[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}
