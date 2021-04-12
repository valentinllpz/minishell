/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:33:39 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/12 17:18:46 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (1);
	return (0);	
}

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

int main()
{
	char	*s;
	t_list	*env;
	char *tmp;

	env = ft_lstnew(ft_strdup("test1=jeej"));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("test2=fuuf  mdr")));
	s = ft_strdup("\"this is a $test1 trop mdr\"");
	s = enclosed_expansion(s, "$test2", env);
	printf("%s\n", s);
	return (0);
}