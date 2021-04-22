/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:38:41 by user42            #+#    #+#             */
/*   Updated: 2021/04/22 12:38:53 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <strings.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/libft.h"

enum	type
{
	WORD,
	AND,
	OR,
	SEMICOLON,
	PIPE,
	RIGHT,
	LEFT,
	DRIGHT,
	DLEFT,
	CMD,
};

typedef	struct s_token
{
	char			*s;
	enum type 		type;
}				t_token;

typedef struct		s_cmd
{
	int				pipe_flag;
	t_list			*exec_lst; // LL car env var
	t_list			*rdir_lst; // content = s_rdir
}					t_cmd;

typedef struct	s_node
{
	enum type 		type; 
	t_list			*cmd_lst; // content = t_cmd
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct		s_rdir
{
	int				flag; // 1 == > // 2 == < // 3 == >> // 4 == <<
	char			*file; // attention aux ambiguous redirect  jeej="file    mdr"     $ echo test > $jeej
}					t_rdir;

typedef struct		s_termios
{

}					t_termios;

typedef struct		s_shell
{
	t_list			*env;
	t_list			*cmd; // à changer ?
	t_list			*tmp_cmd; // à changer ?
	t_list			*tmp_dir; // à changer ?
	t_node			*ast;
	char			*line;
	int				child_status; //à garder ?
	pid_t			pid_pipe;
	pid_t			pid_exec;
	int				pipefd[2];
	int				error_flag;
	int				child_flag; // à voir si à garder
	int				return_value; // à voir si à garder
	struct termios	orig_termios; // ->
	int				flag_termios;
	char			*del_c;		//pas besoin de free
	char			*del_line;	//pas besoin de free, à voir si à garder ou non
	char			*left_c;	//pas besoin de free
	char			*line_up;	//pas besoin de free
	char			*end_line;
	int				nb_col;
	int				pos_x; // set à 3 // <- 
	int				nb_hist;
	t_list			*hist;
	char			*saved_line;
}					t_shell;

//execute1.c
void				ft_exec_cmd(t_node *node, t_shell *shell);
void				ft_process_cmd(t_shell *shell);
void				ft_do_pipes(t_shell *shell);
void				ft_do_dup_child(t_shell *shell);
void				ft_do_dup_parent(t_shell *shell);

//execute2.c
void				launch_execution(t_node *node, t_shell *shell);

//expansion.c
char				*find_match_in_env(char *s, int *len, t_list *env);
char				*replace_var(char *s, int i, t_list *env);
char				*expand_content(char *s, t_list *env);
int					check_dollar_sign(char *s);
void				replace_elem(t_token **content, t_list *elem, t_list *prev);
void				expansion_in_exec_lst(t_list *exec_lst, t_list *env);
int					is_ambiguous_redirect(char *s);
void				expansion_in_rdir_lst(t_list *rdir_lst, t_list *env);

// FREE_AST.C
void				free_rdir(t_rdir *rdir);
void				free_cmd(t_cmd *cmd);
void				free_cmd_lst(t_list *cmd_lst);
void				free_node(t_node *node);
void				free_ast(t_node *ast);

// LEXER.C
t_token				*new_token(char *s);
int					word_count(char *s);
t_token				*build_token(char *s, int *i);
t_token				**ft_lexer(char *s);

// PARSER1.C
int			syntax_err(t_token **lexer, int	i);
int			syntax_check(t_token **lexer);
int			find_separator(t_token **lexer);
t_node		*ft_new_node(enum type type, t_list *cmd_lst);
t_node		*parser(t_token **lexer);

// PARSER2.C
int			add_to_cmd_lst(t_cmd **cmd, t_list **cmd_lst, int pipe_flag);
int			add_to_rdir_lst(t_token **lexer, int *i, t_cmd *cmd);
int			add_to_exec_lst(t_token **lexer, t_cmd *cmd, int i);
t_node		*build_node(t_token **lexer);
t_node		*build_tree(t_token **lexer);

// QUOTES.C

char	*make_unquoted_str(char *s, int *i);
void		quotes_removal(char **s);

// READLINE1.C
void	ft_del_char(t_shell *shell);
void	ft_add_char(char c, t_shell *shell);
void	ft_analyse_del(t_shell *shell);
void	ft_analyse_c(char c, t_shell *shell);
void	ft_readline(t_shell *shell);

// READLINE2.C
void	ft_add_to_hist(t_shell *shell);
void	ft_unwrite_line(t_shell *shell);
void	ft_write_line(t_shell *shell);
void	ft_process_arrow_up(t_shell *shell);
void	ft_analyse_escp(t_shell *shell);

// READLINE3.C
void	ft_process_arrow_down(t_shell *shell);

// REDIRECTIONS.C
void	ft_redirect_from(t_shell *shell);
void	ft_redirect_to_append(t_shell *shell);
void	ft_redirect_to(t_shell *shell);
void	ft_do_redirections(t_shell *shell);

// SAFER LIBFT
int         ft_isprint_safe(int c);
size_t		ft_strlen_safe(const char *s);
char		*ft_strdup_safe(const char *src);

// TERMINAL.C
void	param_termcap3(t_shell *shell);
void	param_termcap2(t_shell *shell);
void	param_termcap(t_shell *shell);
void	enable_raw_mode(t_shell *shell);

// UTILS.C
int					is_space(char c);
int					is_escaped(char *s, int pos);
void				skip_spaces(char *str, int *i);
t_token				**free_lexer(t_token **lexer);
int					is_special(char *s, int i);
char				*join_three_str(char *s1, char *s2, char *s3);
void				skip_to_next_valid_quote(char *s, int *i);

// UTILS1.c
void	ft_incr_pos_x(t_shell *shell);
int		ft_putchar(int c);
int		ft_iscntrl(char c);
void	ft_lstclear_env(t_list **lst);
void	ft_error_bis(t_shell *shell);

// UTILS2.c
void	free_global_struct(t_shell *shell);
void	ft_do_ctrl_d(t_shell *shell);
void	ft_error(t_shell *shell);
char	*ft_get_history(t_shell *shell);


// MAIN ???

t_node	*ft_launch_lexer(char *line);
void	ft_exit(t_shell *shell);
t_shell	*init_shell(void);
void	get_list_env(char **env, t_shell *shell);

// PRINT_LEXER_PARSER.C -- to delete before eval
void	print_lexer(t_token **lexer, char *s);
void	print_exec_lst(t_list *exec_lst);
void	print_rdir_lst(t_list *rdir_lst);
void	print_children(t_node *node, int tree_pos);
void	print_ast_node(t_node *node, int tree_pos);
void	print_parser(t_node *ast);

#endif
