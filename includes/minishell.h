/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:38:41 by user42            #+#    #+#             */
/*   Updated: 2021/03/24 17:56:05 by vlugand-         ###   ########.fr       */
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
	UNKNOWN,
	WORD,
	AND,
	OR,
	SEMICOLON,
	PIPE,
	RIGHT,
	LEFT,
	DRIGHT,
	DLEFT,
};

typedef	struct s_token
{
	char			*s;
	enum type 		type;
}				t_token;

typedef struct	s_node
{
	void			*token;	
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

// UTILS.C
int			is_space(char c);
int			is_escaped(char c, char *s, int i);
void		skip_spaces(char *str, int *i);
t_token		**free_lexer(t_token **lexer);

// LEXER.C
t_token		**ft_lexer(char *s);

#endif
