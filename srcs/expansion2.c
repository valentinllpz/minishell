/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:57:58 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/01 11:17:55 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_enclosed_in_dq(char *s, int i)
{
	int		dq_flag;

	dq_flag = 0;
	while (i >= 0)
	{
		if (s[i] == '\"' && !is_escaped(s, i))
			dq_flag++;
		i--;
	}
	if (dq_flag % 2 != 0)
		return (1);
	return (0);
}

char	*dollar_question_mark(char *s, int *len, int return_value)
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

char	*replace_var(char *s, int i, t_list *env, int return_value)
{
	char	*match;
	char	*outlier;
	char	*dst;
	int		len;
	int		dq_flag;

	len = 0;
	dq_flag = is_enclosed_in_dq(s, i);
	match = find_match_in_env(s + i + 1, &len, env, dq_flag);
	outlier = dollar_question_mark(s + i + 1, &len, return_value);
	s[i] = '\0';
	if (match)
	{
		dst = join_three_str(s, match, s + i + len + 1);
		free(match);
	}
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

char	*find_match_in_env(char *s, int *len, t_list *env, int dq_flag)
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
			return (preserve_literal_value((char *)(env->content)
				+ *len + 1, dq_flag));
		env = env->next;
	}
	return (NULL);
}

char	*expand_content(char *s, t_list *env, int return_value)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !is_escaped(s, i) && !is_enclosed_in_dq(s, i))
		{
			i = get_next_valid_quote_index(s, i);
			i++;
		}
		else if (s[i] == '$' && !is_escaped(s, i)
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '?'))
		{
			s = expand_content
				(replace_var(s, i, env, return_value), env, return_value);
			break ;
		}
		else
			i++;
	}
	return (s);
}
