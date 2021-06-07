/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:05:54 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/07 16:41:53 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_echo_flag(char *arg1)
{
	int		i;

	if (ft_strlen(arg1) < 2)
		return (0);
	if (arg1[0] == '-' && arg1[1] == 'n')
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
	int		nl;
	
	i = 1;
	nl = check_echo_flag(shell->exec[1]);
	if (nl == 1)
		i++;
	while (shell->exec[i])
	{
		ft_putstr_fd(shell->exec[i], 1);
		write(1, " ", 1);
		i++;
	}
	if (nl == 0)
		write(1, "\n", 1);
	shell->return_value = 0;
}