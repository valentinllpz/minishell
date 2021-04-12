/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:27:23 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/12 18:23:25 by vlugand-         ###   ########.fr       */
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

char	*enclosed_expansion(char *s, char *var, t_list *env)
{
	int		len1;
	int		len2;
	char	*dst;
	
	len1 = 0;
	while (s[len1] && s[len1] != '$')
		len1++;
	len2 = ft_strlen(var);
	while (env)
	{
		if ((dst = ft_strnstr(((char *)(env->content)), var + 1, len2 - 1)) && dst[len2 - 1] == '=')
		{
			s[len1] = '\0';
			dst = join_three_str(s, dst + len2, s + len1 + len2);
			free(s);
			return (dst);
		}
		env = env->next;
	}
	return (NULL);
}

char		*get_var_to_expand(char *s, int *flag_q)
{
	int		i;
	int		len;
	char	c;
	char	*dst;

	i = 0;
	len = 0;
	if (s && (s[0] == "\'" || s[0] == "\""))
		*flag_q = 1;
	while (s[i])
	{
		if (s[i] == '$' && !is_escaped('$', s, i))
		{
			while (s[i + len] && !is_space(s[i + len]))
				len++;
			c = s[i + len];
			s[i + len] = '\0';
			if (!(dst = ft_strdup(s + i)))
				return (NULL);
			s[i + len] = c;
			return (dst);
		}
		i++;
	}
	return (NULL);
}

t_list		*var_tokenizer(char *var)
{
	char	**split;
	int		i;
	t_list	*lst;
	
	i = 0;
	lst = NULL;
	split = ft_split(var, ' ');
	while (split[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(split[i]));
		i++;
	}
	free(split);
	return (lst);
}

t_list		*regular_expansion(t_list *exec_lst, char *var, t_list *env)
{
	int		len;
	char	*tmp;
	t_list	*old_node;

	len = ft_strlen(var);
	while (env)
	{
		if ((tmp = ft_strnstr((char *)(env->content), var + 1, len - 1)) && tmp[len - 1] == '=')
		{
			old_node = exec_lst;
			exec_lst = var_tokenizer(tmp + len);
			ft_lstadd_back(&exec_lst, old_node->next);
			free(old_node->content);
			free(old_node);
			return (exec_lst);
		}
		env = env->next;
	}
	return (NULL);
}

void		env_var_expansion1(t_list *exec_lst, t_list *env)
{	
	int		flag_q;
	char	*var;
	
	while (exec_lst)
	{
		flag_q = 0;
		var = get_var_to_expand((char *)(exec_lst->content), &flag_q);
		if (var && !flag_q)
			exec_lst = regular_expansion(exec_lst, var, env);
		else if (var && flag_q)
			exec_lst->content = enclosed_expansion((char *)(exec_lst->content), var, env);
		else
			exec_lst = exec_lst->next;
		if (var)
			free(var);
	}
}
/*
void		env_var_expansion2(t_list *rdir_lst, t_list *env)
{	
	int		flag_q;
	char	*var;
	
	while (rdir_lst)
	{
		flag_q = 0;
		var = get_var_to_expand((t_rdir *)(rdir_lst->content)->file, &flag_q);
		if (var && !flag_q)
			exec_lst = regular_expansion(exec_lst, var, env);
		else if (var && flag_q)
			exec_lst->content = enclosed_expansion((char *)(exec_lst->content), var, env);
		else
			exec_lst = exec_lst->next;
		if (var)
			free(var);
	}
}
*/
// quotes issue with lexer !!!!!!!!!!!!!
//remove quotes
// add shell lvl
// what if malloc fails?
// think about the case where the var is between quotes --> maybe send a struct with the var + a flag if between quotes ?