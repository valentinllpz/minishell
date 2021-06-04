/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:52:27 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/04 20:06:17 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	i = 1;
	while (shell->exec[i] != NULL)
	{
		if (ft_check_var_all(shell->exec[i]) == 1)
		{
			write(1, "export: \'", 9);
			write(1, shell->exec[i], ft_strlen(shell->exec[i]));
			write(1, "\': not a valid identifier\n", 26);
		}
		else if (env_exists(shell->env, shell->exec[i],
		ft_strlen(shell->exec[i])) == 1)
		{
			//FONCTION POUR ENLEVER DE ENV
		}
	}
}