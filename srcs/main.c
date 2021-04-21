/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:40:41 by user42            #+#    #+#             */
/*   Updated: 2021/04/18 17:02:32 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node		*ft_launch_lexer(char *line)
{
	t_token		**lexer;
	t_node		*ast;

	if (!(lexer = ft_lexer(line)))
		return (0); 
	// print_lexer(lexer, line); // print to debug
	if(!(ast = parser(lexer)))
		return (0);
//	print_parser(ast); // print to debug
//	free_ast(ast); 
//	system("leaks minishell");// uncomment to test leaks on mac os
	return (ast);
}

void	ft_exit(void)	// a revoir selon parsing et code
{
	free_global_struct();
	exit(1);
}

void    init_shell(void)
{
	g_shell = malloc(sizeof(t_shell) * 1);
	if (g_shell == NULL)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	g_shell->env = NULL;
	g_shell->line = NULL;
	g_shell->tmp_cmd = NULL;
	g_shell->cmd = NULL;
	g_shell->child_flag = 0;
	g_shell->flag_termios = 0;
	g_shell->pos_x = 3;
	g_shell->nb_hist = 0;
	g_shell->hist = NULL;
	g_shell->saved_line = NULL;
	g_shell->return_value = 0;
	g_shell->pid_pipe = 0;
	g_shell->pid_exec = 0;
	g_shell->error_flag = 0;
}

void    get_list_env(char **env)
{
	int     i;
	t_list  *tmp;

	i = 0;
	while (env[i] != NULL)
	{
		tmp = ft_lstnew(env[i]);
		if (tmp == NULL)
			ft_error();
		ft_lstadd_back(&g_shell->env, tmp);
		i++;
	}
}

int     main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	init_shell(); // a revoir selon parsing et code
	enable_raw_mode();
	get_list_env(env);
	param_termcap();
	ft_readline();
	return (0);
}