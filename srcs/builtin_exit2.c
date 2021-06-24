/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 21:07:10 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/24 21:10:56 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_exit3(t_shell *shell)
{
	if (shell->child_flag == 0)
		write(1, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	write(2, shell->exec[1], ft_strlen_safe(shell->exec[1]));
	write(2, ": numeric argument required\n", 29);
	shell->return_value = 255;
	if (shell->child_flag == 0)
	{
		free_global_struct(shell);
		exit(255);
	}
}
