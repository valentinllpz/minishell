/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:40:41 by user42            #+#    #+#             */
/*   Updated: 2021/06/09 16:59:45 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_launch_lexer(char *line)
{
	t_token		**lexer;
	t_node		*ast;

	if (!(lexer = ft_lexer(line)))
		return (0);
	//print_lexer(lexer, line); // print to debug
	if (!(ast = parser(lexer)))
		return (0);
	// print_parser(ast); // print to debug
	//	free_ast(ast);
	//	system("leaks minishell");// uncomment to test leaks on mac os
	return (ast);
}

void	ft_exit(t_shell *shell)	// a revoir selon parsing et code
{
	free_global_struct(shell);
	exit(1);
}

t_shell	*init_shell(void)
{
	t_shell	*shell;
	char	*buf;

	shell = malloc(sizeof(t_shell) * 1);
	if (shell == NULL)
	{
		buf = strerror(errno);
		write(2, buf, ft_strlen_safe(buf));
		write(2, "\n", 1);
		exit(1);
	}
	shell->term = malloc(sizeof(t_term) * 1);
	if (shell->term == NULL)
	{
		free(shell);
		buf = strerror(errno);
		write(2, buf, ft_strlen_safe(buf));
		write(2, "\n", 1);
		exit(1);
	}
	shell->env = NULL;
	shell->line = NULL;
	shell->tmp_cmd = NULL;
	shell->child_flag = 0;
	shell->term->flag_termios = 0;
	shell->term->pos_x = 12;
	shell->nb_hist = 0;
	shell->hist = NULL;
	shell->saved_line = NULL;
	shell->return_value = 0;
	shell->pid_pipe = 0;
	shell->pid_exec = 0;
	shell->error_flag = 0;
	shell->envp = NULL;
	shell->exec = NULL;
	shell->path = NULL;
	shell->exec_status = 0;
	shell->pipe_status = 0;
	if (tcgetattr(STDIN_FILENO, &shell->term->orig_termios) == -1)
		ft_error(shell);
	shell->term->flag_termios = 1;
	shell->tmp_stdin = 0;
	shell->tmp_stdout = 0;
	return (shell);
}

void	get_list_env(char **env, t_shell *shell)
{
	int		i;
	t_list	*tmp;
	char	*tmp_char;

	i = 0;
	while (env[i] != NULL)
	{
		tmp_char = ft_strdup(env[i]);
		if (tmp_char == NULL)
			ft_error(shell);
		tmp = ft_lstnew(tmp_char);
		if (tmp == NULL)
		{
			free(tmp_char);
			ft_error(shell);
		}
		ft_lstadd_back(&shell->env, tmp);
		i++;
	}
}

int		main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(); // a revoir selon parsing et code
	get_list_env(env, shell);
	param_termcap(shell);
	ft_readline(shell);
	return (0);
}
