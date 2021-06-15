/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:57:58 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/15 15:06:06 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*exp_outliers(char *s, int *len, int return_value)
{
	if (s)
	{
		if (*len == 0 && s[0] == '?')
		{
			(*len)++;
			return (ft_itoa(return_value));
		}
	}
	return (NULL);
}

char	*find_match_in_env(char *s, int *len, t_list *env)
{
	while (s[*len])
	{
		if (!ft_isalnum(s[*len]))
			break ;
		(*len)++;
	}
	while (env)
	{
		if (*len > 0 && ft_strncmp(s, (char *)(env->content), *len) == 0
		&& ((char *)(env->content))[*len] == '=')
			return ((char *)(env->content) + *len + 1);
		env = env->next;
	}
	return (NULL);
}

char	*replace_var(char *s, int i, t_list *env, int return_value)
{
	char	*match;
	char	*outlier;
	char	*dst;
	int		len;

	len = 0;
	match = find_match_in_env(s + i + 1, &len, env);
	outlier = exp_outliers(s, &len, return_value);
	s[i] = '\0';
	if (match)
		dst = join_three_str(s, match, s + i + len + 1);
	else if (outlier)
	{
		dst = join_three_str(s, outlier, s + i + len + 1);
		free(outlier);
	}
	else
		dst = join_three_str(s, "", s + i + len + 1);
	free(s);
	return (dst);
}

char	*expand_content(char *s, t_list *env, int return_value)
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
		else if (s[i] == '$' && !is_escaped(s, i) && (ft_isalnum(s[i + 1]) || s[i + 1] == '?'))
		{
			s = expand_content(replace_var(s, i, env, return_value), env, return_value);
			break ;
		}
		else
			i++;
	}
	return (s);
}
