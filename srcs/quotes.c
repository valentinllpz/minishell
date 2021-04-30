/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:46:43 by vlugand-          #+#    #+#             */
/*   Updated: 2021/04/30 16:10:00 by ade-garr         ###   ########.fr       */
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

void	quotes_removal(char **s)
{
	int		i;
	char	*dst;

	i = 0;
	while ((*s)[i])
	{
		if (((*s)[i] == '\'' || (*s)[i] == '\"') && !is_escaped(*s, i))
		{
			dst = make_unquoted_str(*s, &i);
			free(*s);
			*s = dst;
			i -= 2;
		}
		i++;
	}
}

/*
int main(int ac, char **av)
{
	char *s;

	s = ft_strdup(av[1]);
	printf("before s = [%s]\n", s);
	quotes_removal(&s);
	printf("after s = [%s]\n", s);
	return (0);
}*/
