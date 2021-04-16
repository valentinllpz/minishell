/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:33:39 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/16 18:23:17 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*join_three_str(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	int		len;
	char	*dst;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(dst = malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	j = i;
	i = -1;
	while (s2[++i])
		dst[j + i] = s2[i];
	j += i;
	i = -1;
	while (s3[++i])
		dst[j + i] = s3[i];
	dst[j + i] = '\0';
	return (dst);
}


char	*find_match_in_env(char *s, int *len, t_list *env)
{
	int		i;
	
	i = 0;
	while (s[i])
	{
		if ((s[i] == '\'' && !is_escaped(s, i))
		|| (s[i] == '\"' && !is_escaped(s, i))
		|| (s[i] == '$' && !is_escaped(s, i)))
			break ;
		i++;
	}
	*len = i;
	while (env)
	{
		if (i > 0 && ft_strncmp(s, (char *)(env->content), i) == 0 && ((char *)(env->content))[i] == '=')
			return ((char *)(env->content) + i + 1);
		env = env->next;
	}
	return (NULL);
}

char	*replace_var(char *s, int i, t_list *env)
{
	char	*match;
	char	*dst;
	int		len;

	len = 0;
	match = find_match_in_env(s + i + 1, &len, env);
	s[i] = '\0';
	if (match)
		dst = join_three_str(s, match, s + i + len + 1);
	else
		dst = join_three_str(s, "", s + i + len + 1);
	free(s);
	return (dst);
}

char	*expand_content(char *s, t_list *env)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !is_escaped(s, i))
		{
			skip_to_next_valid_quote(s, &i);
			i++;
		}
		if (s[i] == '$' && !is_escaped(s, i))
			s = replace_var(s, i, env);
		else
			i++;
	}
	return (s);
}

int		check_dollar_sign(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && !is_escaped(s, i))
			return (1);
		i++;
	}
	return (0);
}

void		replace_elem(t_token **content, t_list *elem, t_list *prev)
{
	int			i;
	t_list		*lst;

	i = 0;
	lst = NULL;
	while (content[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(content[i]->s)));
		i++;
	}
	ft_lstadd_back(&lst, elem->next);
	free_lexer(content);
	free(elem->content);
	free(elem);
	prev->next = lst;
}

void	expansion_in_exec_lst(t_list *exec_lst, t_list *env)
{
	t_list		*prev;

	prev = NULL;
	while (exec_lst)
	{
		if (check_dollar_sign(exec_lst->content))
		{
			if (!(exec_lst->content = expand_content(exec_lst->content, env)))
			{
				prev->next = exec_lst->next;
				free(exec_lst);
			}
			replace_elem(ft_lexer(exec_lst->content), exec_lst, prev);
		}
		prev = exec_lst;
		exec_lst = exec_lst->next;
	}
}
/*
int main(int ac, char **av)
{
	t_list *exec_lst;
	t_list *env;
	char *s;
	int		i;

	i = 0;
	env = ft_lstnew(ft_strdup("test1=fucking "));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("test2=working")));
	exec_lst = ft_lstnew(ft_strdup("thereisnothinghere"));
	ft_lstadd_back(&exec_lst, ft_lstnew(ft_strdup("ihopeits$test1\"$test2\"")));
	expansion_in_exec_lst(exec_lst, env);
	while (exec_lst)
	{
		printf("token %i %s\n", i, exec_lst->content);
		i++;
		exec_lst = exec_lst->next;
	}
	return 0;
}	
*/