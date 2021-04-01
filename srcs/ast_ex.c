/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:39:42 by vlugand-          #+#    #+#             */
/*   Updated: 2021/03/19 13:02:38 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

enum type
{
	NB,
	PLUS,
	MINUS,
	MULTIPLY,
} ;

typedef struct		s_node
{
	int				value;
	int				type; // 1 = + ;  2 = - ; 3 = * //
	struct s_node	*left;
	struct s_node	*right;
}					t_node;


t_node			*ft_new_node(int value, int type);
int				evaluate_node(t_node *node);
t_node 			*build_tree(char **split, int i, int type);
int				find_op(char **split, char c);
t_node			*parser(char **split);
char			**lexer(char *s);


t_node	*ft_new_node(int value, int type)
{
	t_node	*node;

	if (!(node = ft_calloc(sizeof(t_node), 1)))
		return (NULL);
	node->value = value;
	node->type = type;
	return (node);
}

int		evaluate_node(t_node *node)
{
	if (node->type == PLUS)
		return (evaluate_node(node->left) + evaluate_node(node->right));
	else if (node->type == MINUS)
		return (evaluate_node(node->left) - evaluate_node(node->right));
	else if (node->type == MULTIPLY)
		return (evaluate_node(node->left) * evaluate_node(node->right));
	else
		return (node->value);
}

int		find_op(char **split, char c)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == c)
			return (i);
		i++;
	}
	return (0);
}

t_node *build_tree(char **split, int i, int type)
{
	t_node  *node;
	char	*tmp;
	static int node_nb = 0;

	if (type)
	{
		node = ft_new_node(0, type);
		tmp = split[i];
		split[i] = NULL;             // separates whats before and after the sign
		node->left = parser(split);
		split[i] = tmp;
		node->right = parser(split + i + 1);
	}
	else
		node = ft_new_node(ft_atoi(split[i]), 0);
	return (node);
}

void print_split(char **split)
{
	int i = 0;
	static int j = 1;

	while(split[i])
	{
		printf("(call %i) : split[%i] = \"%s\"\n", j, i, split[i]);
		i++;
	}
	j++;
	printf("\n\n");
}

t_node	*parser(char **split)
{
	int		i;
	t_node  *node;

	i = 0;
//	print_split(split); // DEBUG
	if ((i = find_op(split, '+')))  // 1st OP of lesser priority is found
		node = build_tree(split, i, PLUS);
	else if ((i = find_op(split, '-')))
		node = build_tree(split, i, MINUS);
	else if ((i = find_op(split, '*')))
		node = build_tree(split, i, MULTIPLY);
	else
		node = build_tree(split, i, NB);
	return (node);
}

char	**lexer(char *s)
{
	char	**split;

	split = ft_split(s, ' ');
	return (split);
}

int		main(int ac, char **av)
{
	t_node	*node;
	char	**split;
	int		res;

	split = lexer(av[1]);
	node = parser(split);
	res = evaluate_node(node);
	printf("value is %i\n", res);
	return (0);
}