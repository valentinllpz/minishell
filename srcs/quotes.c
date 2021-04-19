/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:46:43 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/19 16:56:32 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*make_unquoted_str(char *s, int *i)
{
	int		j;
	char	c;
	char	*tmp1;
	char	*tmp2;
	char	*dst;

	j = *i;
	c = s[*i];
	s[*i] = '\0';
	tmp1 = ft_strdup(s);
	s[*i] = c;
	skip_to_next_valid_quote(s, i);
	s[*i] = '\0';
	tmp2 = ft_strdup(s + j + 1);
	dst = join_three_str(tmp1, tmp2, s + *i + 1);
	if (tmp1)
		free(tmp1);
	if (tmp2)
		free(tmp2);
	return (dst);
}

void		quotes_removal(char **s)
{
	int		i;
	int		j;
	char	*tmp1;
	char	*tmp2;
	char	*dst;

	i = 0;
	while ((*s)[i])
	{
		if (((*s)[i] == '\'' || (*s)[i] == '\"')  && !is_escaped(*s, i))
		{
			dst = make_unquoted_str(*s, &i);
			free(*s);
			*s = dst;
			i -= 2;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	char *s1 = "this";
	char *s2 = NULL;
	char *s3 = " works";
	
	printf("[%s]\n", join_three_str(s1, s2, s3));
	return (0);
}