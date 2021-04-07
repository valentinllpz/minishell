/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:38:41 by user42            #+#    #+#             */
/*   Updated: 2021/04/07 17:35:36 by vlugand-         ###   ########.fr       */
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
	char			*file;
}					t_rdir;


// UTILS.C
int			is_space(char c);
int			is_escaped(char c, char *s, int i);
void		skip_spaces(char *str, int *i);
t_token		**free_lexer(t_token **lexer);
int			is_special(char *s, int i);

// LEXER.C
t_token		*new_token(char *s);
void		skip_to_next_valid_quote(char *s, int *i);
t_token		*build_token(char *s, int *i);
int			word_count(char *s);
t_token		**ft_lexer(char *s);

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

// FREE_AST.C
void	free_rdir(t_rdir *rdir);
void	free_cmd(t_cmd *cmd);
void	free_cmd_lst(t_list *cmd_lst);
void	free_node(t_node *node);
void	free_ast(t_node *ast);

// PRINT_LEXER_PARSER.C -- to delete before eval
void	print_lexer(t_token **lexer, char *s);
void	print_exec_lst(t_list *exec_lst);
void	print_rdir_lst(t_list *rdir_lst);
void	print_children(t_node *node, int tree_pos);
void	print_ast_node(t_node *node, int tree_pos);
void	print_parser(t_node *ast);
#endif
