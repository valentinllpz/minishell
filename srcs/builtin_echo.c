/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:05:54 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/23 15:36:11 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_echo_flag(char *arg1)
{
	int		i;

	if (arg1 && ft_strlen(arg1) < 2)
		return (0);
	if (arg1 && arg1[0] == '-' && arg1[1] == 'n')
	{
		i = 1;
		while (arg1[i] == 'n')
			i++;
		if (arg1[i] == '\0')
			return (1);
	}
	return (0);
}

void	builtin_echo(t_shell *shell)
{
	int		i;
	int		nl_flag;

	i = 1;
	nl_flag = check_echo_flag(shell->exec[i]);
	while (shell->exec[i] && check_echo_flag(shell->exec[i]))
		i++;
	while (shell->exec[i])
	{
		if (shell->exec[i])
			ft_putstr_fd(shell->exec[i], 1);
		if (shell->exec[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl_flag == 0)
		write(1, "\n", 1);
	shell->return_value = 0;
}
