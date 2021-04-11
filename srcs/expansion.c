/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:27:23 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/11 17:30:43 by vlugand-         ###   ########.fr       */
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

void		enclosed_expansion(char **s, char *var, t_list *env)
{
	int		len1;
	int		len2;
	char	*tmp;
	
	len1 = 0;
	while ((*s)[len1] && (*s)[len1] != '$')
		len1++;
	len2 = ft_strlen(var);
	while (env)
	{
		if ((tmp = ft_strnstr(((char *)(env->content)), var + 1, len2 - 1)) && tmp[len2 - 1] == '=')
		{
			(*s)[len1] = '\0';
			tmp = join_three_str(*s, tmp + len2, *s + len1 + len2);
			free(*s);
			*s = tmp;
		}
		env = env->next;
	}
}

int			token_is_expandable(char *s)
{
	int		i;
	int		flag_quotes;

	i = 0;
	flag_quotes = 0;
	if (s && (s[0] == "\'" || s[0] == "\""))
		flag_quotes = 1;
	while (s[i])
	{
		if (s[i] == '$' && !is_escaped('$', s, i))
			return (1 + flag_quotes);
		i++;
	}
	return (0);
}

t_list		*var_tokenizer(char *var)
{
	char	**split;
	int		i;
	t_list	*lst;

	split = ft_split(var, ' ');
	while (split[i])
	{
		lst = ft_lstnew(split[i]);
		lst = lst->next;
		i++;
	}
	free(split);
	return (lst);
}

void		replace_token(t_list *exec_lst, t_list *env)
{
	int		len;
	char	*var;
	t_list	*tmp1;

	len = ft_strlen(((char *)(exec_lst->content))) - 1;//we don't count the $
	while (env)
	{
		if ((var = ft_strnstr(((char *)(env->content) + 1), ((char *)(exec_lst->content)), len)) && var[len] == '=')
		{
			tmp1 = exec_lst;
			exec_lst = var_tokenizer(var + len + 1);//we send only the part after =
			while (exec_lst)
				exec_lst = exec_lst->next;
			exec_lst->next = tmp1;
			return (exec_lst);
		}
		env = env->next;
	}
	return (NULL);
}

void		env_var_expansion(t_list *exec_lst, t_list *rdir_lst, t_list *env)
{	
	while (exec_lst)
	{
		if (token_is_expandable(((char *)(exec_lst->content))) == 1)
			exec_lst = replace_token(exec_lst, env);
		exec_lst = exec_lst->next;
	}
	// check aussi file dans rdir
}

//remove quotes
// add shell lvl
// think about the case where the var is between quotes --> maybe send a struct with the var + a flag if between quotes ?