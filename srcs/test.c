/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:33:39 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/15 17:22:21 by vlugand-         ###   ########.fr       */
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

void print_lst(t_list *lst)
{
	while (lst)
	{
		printf("main : %s | %p\n", lst->content, lst);
		lst = lst->next;
	}
}

void	replace_elem(t_list **elem, t_list *prev, t_list *next, t_list *new)
{
	free((*elem)->content);
	free(*elem);
	*elem = new;
	ft_lstlast(*elem)->next = next;
}

t_list		*env_var_tokenizer(char *s)
{
	char	**split;
	int		i;
	t_list	*lst;
	
	i = 0;
	lst = NULL;
	if (!s)
		return (NULL);
	split = ft_split(s, ' ');
	while (split[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(split[i]));
		i++;
	}
	free(split);
	return (lst);
}


char	*find_match_in_env(char *s, int *len, t_list *env)
{
	int		i;
	
	i = 0;
	while (s[i])
	{
		if ((s[i] == '\'' && !is_escaped('\'', s, i))
		|| (s[i] == '\"' && !is_escaped('\"', s, i))
		|| (s[i] == '$' && !is_escaped('$', s, i)))
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
		if (s[i] == '\'' && !is_escaped('\'', s, i))
		{
			skip_to_next_valid_quote(s, &i);
			i++;
		}
		if (s[i] == '$' && !is_escaped('$', s, i))
			s = replace_var(s, i, env);
		else
			i++;
	}
	return (s);
}

char	*check_dollar_sign(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && !is_escaped('$', s[i], i))
			return (1);
		i++;
	}
	return (0);
}

void	expansion_in_exec_lst(t_list *exec_lst, t_list *env)
{
	t_list *prev;
	
	prev = NULL;
	while (exec_lst)
	{
		if (check_dollar_sign(exec_lst->content))
			exec_lst->content = expand_token(&exec_lst, prev, exec_lst->content, env);
		prev = exec_lst;
		exec_lst = exec_lst->next;
	}
	
}


int main(int ac, char **av)
{
	t_list *env;
	char *s;

	s = ft_strdup("'$test1'\"thisis\"$lol$test1\"$test2\"");
	env = ft_lstnew(ft_strdup("test1=fucking "));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("test2=working")));
	s = expand_content(s, env);
	printf("%s\n", s);
	return 0;
}
/*
int main()
{
	t_list	*lst;
	t_list	*new;

	lst = ft_lstnew(ft_strdup("one"));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("$")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("four")));
	print_lst(lst);
	new = ft_lstnew(ft_strdup("two"));
	ft_lstadd_back(&new, ft_lstnew(ft_strdup("three")));
	replace_elem(&(lst->next), lst, lst->next->next, new);
	print_lst(lst);
	while (lst)
	{
		free(lst->content);
		free(lst);
		lst = lst->next;
	}
	return (0);
}


int main()
{
	char	*s;
	t_list	*env;
//	t_list	*exec_lst;
	char *tmp;

	env = ft_lstnew(ft_strdup("test1=jeej"));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("test2=fuuf  mdr")));
//	exec_lst = ft_lstnew(ft_strdup("$test1"));
//	ft_lstadd_back(&exec_lst, ft_lstnew(ft_strdup("\"this is a $test1 $test2 trop mdr\"")));
	exec_lst = expansion_in_exec_lst(exec_lst, env);
	return (0);
}*/