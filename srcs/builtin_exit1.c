/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:02:48 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/25 16:56:19 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long	get_k_value(char *s)
{
	int					i;
	unsigned long long	k;
	int					neg;

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
	if (neg == 1)
		return ((long long) -k);
	else
		return ((long long)k);
}

int	check_k(unsigned long long k, int neg)
{
	if (k > 9223372036854775807)
	{
		if (neg == 0)
			return (1);
		else if (k - 1 > 9223372036854775807)
			return (1);
	}
	return (0);
}

int	check_arg_exit(char *s)
{
	int						i;
	int						neg;
	unsigned long long		k;

	k = 0;
	i = -1;
	neg = 0;
	if (s[++i] == '-')
	{
		neg = 1;
		i++;
	}
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) != 1)
			return (1);
		k = k * 10 + ((int)s[i] - 48);
		if (check_k(k, neg) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	builtin_exit2(t_shell *shell)
{
	long long	k;

	if (shell->exec[2] != NULL)
	{
		if (shell->child_flag == 0)
			write(1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->return_value = 1;
	}
	else
	{
		k = get_k_value(shell->exec[1]);
		k = k % 256;
		shell->return_value = (int)k;
		if (shell->child_flag == 0)
		{
			write(1, "exit\n", 5);
			free_global_struct(shell);
			exit((int)k);
		}
	}
}

void	builtin_exit(t_shell *shell)
{
	int	ret;

	if (shell->exec[1] == NULL)
	{
		if (shell->child_flag == 0)
		{
			ret = shell->return_value;
			write(1, "exit\n", 5);
			free_global_struct(shell);
			exit(ret);
		}
	}
	else if (check_arg_exit(shell->exec[1]) == 1)
		builtin_exit3(shell);
	else
		builtin_exit2(shell);
}
