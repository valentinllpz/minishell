/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:52:26 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/19 17:34:29 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (1);
	return (0);	
}

int		is_escaped(char *s, int pos) //ne marche pas pour plusieurs //
{
	int		bs_flag;
	int		i;

	if (pos == 0)
		return (0);
	i = 0;
	bs_flag = 0;
	while (i < pos)
	{
		bs_flag = 0;
		while (s[i] == '\\')
		{
			bs_flag++;
			i++;
		}
		i++;
	}
	if (bs_flag == 0)
		return (0);
	else if (bs_flag % 2 > 0)
		return (1);
	return (0);
}

int			is_special(char *s, int i)
{
	if (s[i] == '\0')
		return (0);
	if (((s[i] == '>' && s[i + 1] == '>') || (s[i] == '&' && s[i + 1] == '&') ||
	(s[i] == '|' && s[i + 1] == '|')) && !is_escaped(s, i))
		return (2);
	else if ((s[i] == ';' || s [i] == '|' || s[i] == '>' || s[i] == '<') && !is_escaped(s, i))
		return (1);
	else
		return (0);
}

int		which_operator(char *s, int i)
{
	if (s[i] == '\0')
		return (0);
	if (s[i] == '&' && s[i + 1] == '&')
		return (AND);
	else if (s[i] == '|' && s[i + 1] == '|')
		return (OR);
	else if (s[i] == ';')
		return (SEMICOLON);
	else if (s[i] == '|')
		return (PIPE);
	else if (s[i] == '>')
		return (RIGHT);
	else if (s[i] == '<')
		return (LEFT);
	else if (s[i] == '>' && s[i + 1] == '>')
		return (DRIGHT);
	else if (s[i] == '<' && s[i + 1] == '<')
		return (DLEFT);
	else
		return (0);
}

void	skip_spaces(char *s, int *i)
{
	while (s[*i] && ((s[*i] > 8 && s[*i] < 14) || s[*i] == ' '))
		(*i)++;
}

void			skip_to_next_valid_quote(char *s, int *i)
{
	if (s[*i] == '\'' && !is_escaped(s, *i))
	{
		(*i)++;
		while (s[*i])
		{
			if (s[*i] == '\'' && !is_escaped(s, *i))
				break ;
			(*i)++;
		}
	}
	else if (s[*i] == '\"' && !is_escaped(s, *i))
	{
		(*i)++;
		while (s[*i])
		{
			if (s[*i] == '\"' && !is_escaped(s, *i))
				break ;
			(*i)++;
		}
	}
}

t_token		**free_lexer(t_token **lexer)
{
	int			i;

	i = 0;
	while (lexer[i])
	{
		free(lexer[i]->s);
		free(lexer[i]);
		i++;
	}
	free(lexer);
	return (NULL);
}

char		*join_three_str(char *s1, char *s2, char *s3)
{
	int		i;
	int		len1;
	int		len2;
	int		len3;
	char	*dst;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	if (s3)
		len3 = ft_strlen(s3);
	else
		len3 = 0;
	if (!(dst = malloc((len1 + len2 + len3 + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(dst, s1, len1 + 1);
	ft_strlcpy(dst + len1, s2, len2 + 1);
	ft_strlcpy(dst + len1 + len2, s3, len3 + 1);
	return (dst);
}

/*char		*join_three_str(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	int		len;
	char	*dst;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(dst = malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	if (!s1)
		ft_strlcpy(dst, s1, ft_strlen(s1));
	while (s1[++i])
		dst[i] = s1[i];
	j = i;
	i = -1;
	if (s2)
		while (s2[++i])
			dst[j + i] = s2[i];
	j += i;
	i = -1;
	if (s3)
		while (s3[++i])
			dst[j + i] = s3[i];
	dst[j + i] = '\0';
	return (dst);
}*/