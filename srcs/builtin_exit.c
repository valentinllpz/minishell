/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:02:48 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/07 18:45:38 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long	get_k_value(char *s)
{
	int			i;
	long long	k;
	int			neg;

	k = 0;
	i = 0;
	neg = 0;
	if (s[i] != '\0' && s[i] == '-')
	{
		neg = 1;
		i++;
	}
	while (s[i] != '\0')
	{
		k = k * 10 + ((int)s[i] - 48);
		i++;
	}
	return ((long)k);
}

int	check_arg_exit(char *s)
{
	int				i;
	int				neg;
	unsigned long	k;

	k = 0;
	i = 0;
	neg = 0;
	if (s[i] == '-')
	{
		neg = 1;
		i++;
	}
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) != 1)
			return (1);
		k = k * 10 + ((int)s[i] - 48);
		if (k > 9223372036854775807)
		{
			if (neg == 0)
				return (1);
			else if (k > 9223372036854775808)
				return (1);
		}
		i++;
	}
}

void	builtin_exit(t_shell *shell)
{
	long	k;

	if (shell->exec[1] == NULL)
	{
		write(1, "exit\n", 5);
		free_global_struct(shell);
		exit(0);
	}
	if (check_arg_exit(shell->exec[1]) == 1)
	{
		write(2, "exit: ", 6);
		write(2, shell->exec[1], ft_strlen_safe(shell->exec[1]));
		write(2, ": numeric argument required\n", 29);
		free_global_struct(shell);
		exit(255);
	}
	else
	{
		if (shell->exec[2] != NULL)
		{
			write(2, "exit: too many arguments\n", 25);
			shell->return_value = 1;
		}
		else
		{
			k = get_k_value(shell->exec[1]);
			k = k % 256;
			write(1, "exit\n", 5);
			free_global_struct(shell);
			exit((int)k);
		}
	}
}
