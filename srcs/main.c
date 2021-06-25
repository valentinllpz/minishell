/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:40:41 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/25 19:06:10 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell();
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	get_list_env(env, shell);
	add_shlvl(shell);
	param_termcap(shell);
	ft_readline(shell);
	return (0);
}
