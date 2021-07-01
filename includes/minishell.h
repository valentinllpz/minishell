/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:38:41 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/01 19:56:09 by ade-garr         ###   ########.fr       */
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
# include <signal.h>
# include "../libft/libft.h"

enum e_type
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

typedef struct s_token
{
	char		*s;
	enum e_type	type;
}				t_token;

typedef struct s_cmd
{
	int			pipe_flag;
	t_list		*exec_lst;
	t_list		*rdir_lst;
}				t_cmd;

typedef struct s_node
{
	enum e_type		type;
	t_list			*cmd_lst;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct s_rdir
{
	int		flag;
	char	*file;
}				t_rdir;

typedef struct s_term
{
	struct termios	orig_termios;
	int				flag_termios;
	char			*del_c;
	char			*del_line;
	char			*left_c;
	char			*line_up;
	char			*end_line;
	int				nb_col;
	int				pos_x;
	int				delta;
}					t_term;

typedef struct s_shell
{
	t_list			*env;
	char			**envp;
	char			**exec;
	char			*path;
	t_list			*tmp_cmd;
	t_list			*tmp_rdir;
	t_node			*ast;
	char			*line;
	int				exec_status;
	int				pipe_status;
	pid_t			pid_pipe;
	pid_t			pid_exec;
	int				pipefd[2];
	int				error_flag;
	int				parent_flag;
	int				child_flag;
	int				return_value;
	t_term			*term;
	int				nb_hist;
	t_list			*hist;
	char			*saved_line;
	int				tmp_stdin;
	int				tmp_stdout;
}				t_shell;

void		builtin_cd_oldpwd2(t_shell *shell, char *path);
void		builtin_cd_oldpwd(t_shell *shell);
void		builtin_cd_home2(t_shell *shell, char *path);
void		builtin_cd_home(t_shell *shell);
void		builtin_cd(t_shell *shell);
void		builtin_cd_norm3(t_shell *shell, char *path);
void		builtin_cd_norm2(t_shell *shell);
void		builtin_cd_norm(t_shell *shell);
int			check_echo_flag(char *arg1);
void		builtin_echo(t_shell *shell);
void		builtin_env(t_shell *shell);
long long	get_k_value(char *s);
int			check_k(unsigned long long k, int neg);
int			check_arg_exit(char *s);
void		builtin_exit(t_shell *shell);
void		builtin_exit2(t_shell *shell);
void		builtin_exit3(t_shell *shell);
int			ft_check_var(char *str);
void		write_var(char *str);
void		builtin_export3(t_shell *shell, int len, int i);
void		builtin_export2(t_shell *shell);
void		builtin_export(t_shell *shell);
void		builtin_pwd(t_shell *shell);
void		unset_var2(t_shell *shell, int i);
void		unset_var(t_shell *shell, int i);
int			ft_check_var_all(char *str);
void		builtin_unset(t_shell *shell);
void		launch_bin(t_shell *shell);
void		launch_builtin(t_shell *shell);
void		ft_do_dup_parent(t_shell *shell);
void		ft_do_dup_child(t_shell *shell);
void		ft_do_pipes(t_shell *shell);
void		ft_process_cmd(t_shell *shell);
void		ft_exec_cmd(t_node *node, t_shell *shell);
int			ft_set_path3(t_shell *shell, char *env_path, char **path_split);
void		ft_set_path2(t_shell *shell, char *env_path);
void		ft_set_path(t_shell *shell);
void		launch_execution(t_node *node, t_shell *shell);
void		ft_execution(t_shell *shell);
void		get_return_value2(t_shell *shell);
void		get_return_value(t_shell *shell);
void		ft_execution2_errno(t_shell *shell);
void		ft_execution2(t_shell *shell);
void		ft_do_first_pipe(t_shell *shell);
int			check_dollar_sign(char *s);
void		replace_elem(t_token **content, t_list *elem);
void		expansion_in_exec_lst(t_list *exec_lst, t_list *env, int ret);
int			is_ambiguous_redirect(char *s);
void		expansion_in_rdir_lst(t_list *rdir_lst, t_list *env, int ret);
int			is_enclosed_in_dq(char *s, int i);
char		*dollar_question_mark(char *s, int *len, int return_value);
char		*replace_var(char *s, int i, t_list *env, int return_value);
char		*find_match_in_env(char *s, int *len, t_list *env, int dq_flag);
char		*expand_content(char *s, t_list *env, int return_value);
char		*add_dquotes_to_str(char *s);
char		*preserve_literal_value(char *match, int dq_flag);
void		free_rdir(t_rdir *rdir);
void		free_cmd(t_cmd *cmd);
void		free_cmd_lst(t_list *cmd_lst);
void		free_node(t_node *node);
void		free_ast(t_node *ast);
void		free_lexer(t_token **lexer);
void		free_charptr(char **ptr);
void		free_global_struct2(t_shell *shell);
void		free_global_struct(t_shell *shell);
void		ft_exit(t_shell *shell);
t_list		*get_heredoc_content(t_shell *shell, char *file);
void		ft_heredoc(t_shell *shell, char *file);
void		init_shell2(t_shell *shell);
t_shell		*init_shell(void);
t_token		*new_token(char *s);
int			word_count(char *s);
t_token		*build_token(char *s, int *i);
t_token		**ft_lexer(char *s);
int			syntax_err(t_token **lexer, int i);
int			syntax_check(t_token **lexer);
int			find_separator(t_token **lexer);
t_node		*ft_new_node(enum e_type type, t_list *cmd_lst);
t_node		*parser(t_token **lexer);
int			add_to_cmd_lst(t_cmd **cmd, t_list **cmd_lst, int pipe_flag);
int			add_to_rdir_lst(t_token **lexer, int *i, t_cmd *cmd);
int			add_to_exec_lst(t_token **lexer, t_cmd *cmd, int i);
t_node		*build_node(t_token **lexer);
t_node		*build_tree(t_token **lexer);
void		ft_del_char(t_shell *shell);
void		ft_add_char(char c, t_shell *shell);
void		ft_analyse_del(t_shell *shell);
void		ft_analyse_c(char c, t_shell *shell);
void		ft_readline(t_shell *shell);
void		ft_add_to_hist(t_shell *shell);
void		ft_unwrite_line(t_shell *shell);
void		ft_write_line(t_shell *shell);
void		ft_process_arrow_up(t_shell *shell);
void		ft_analyse_escp(t_shell *shell);
int			ft_check_line_spaces(char *s);
void		ft_readline_loop2(t_shell *shell);
void		ft_readline_loop(t_shell *shell);
void		ft_process_arrow_down(t_shell *shell);
char		*ft_get_history(t_shell *shell);
void		ft_redirect_from(t_shell *shell);
void		ft_redirect_to_append(t_shell *shell);
void		ft_redirect_to(t_shell *shell);
void		ft_do_redirections(t_shell *shell);
void		handler(int sig);
void		ft_do_ctrl_c(t_shell *shell);
void		ft_do_ctrl_d(t_shell *shell);
void		rm_backslash_outside_quotes(char *s, char *dst, int *i, int *j);
void		rm_backslash_in_dquotes(char *s, char *dst, int *i, int *j);
void		rm_quotes(char *s, char *dst, int *i, int *j);
char		*str_cleanup(char *s);
void		param_termcap3(t_shell *shell);
void		param_termcap2(t_shell *shell);
void		param_termcap(t_shell *shell);
void		enable_raw_mode(t_shell *shell);
int			is_space(char *s, int i);
int			is_escaped(char *s, int pos);
int			is_special(char *s, int i);
int			is_defined(char *s);
void		get_list_env(char **env, t_shell *shell);
char		**ft_list_env_to_char(t_list *lst);
int			env_exists(t_list *env, char *var, int len);
char		*get_value_from_env(t_list *env, char *var, int len);
int			ft_lstsize_env(t_list *lst);
void		change_value_from_env2(t_list *env, char *value, int len);
void		change_value_from_env(t_list *env, char *value, char *var, int len);
void		change_variable_in_env(t_list *env, char *str, int len);
int			get_len_var(char *s);
int			ft_check_path(t_shell *shell);
int			ft_lstsize_exec(t_list *lst);
char		**ft_list_to_char(t_list *lst);
void		ft_error(t_shell *shell);
void		add_shlvl(t_shell *shell);
void		ft_sort_tab(char **tb);
void		skip_spaces(char *s, int *i);
int			get_next_valid_quote_index(char *s, int i);
char		*join_three_str(char *s1, char *s2, char *s3);
int			ft_isprint_safe(int c);
size_t		ft_strlen_safe(const char *s);
char		*ft_strdup_safe(const char *src);
void		ft_incr_pos_x(t_shell *shell);
int			ft_putchar(int c);
void		disable_raw_mode(t_shell *shell);
int			get_cursor_pos(t_shell *shell);

#endif
