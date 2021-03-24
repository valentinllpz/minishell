/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:58:04 by vlugand-          #+#    #+#             */
/*   Updated: 2021/03/11 15:49:17 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && ((str[*i] > 8 && str[*i] < 14) || str[*i] == ' '))
		(*i)++;
}

int		which_operator(char *str, int i)
{
	if (str[i] == '\0')
		return (0);
	else if (str[i] == ';')
		return (1);
	else if (str[i] == '|')
		return (2);
	else if (str[i] == '>')
		return (3);
	else if (str[i] == '<')
		return (4);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (5);
	else
		return (0);
}

int		is_odd(int nb)
{
	int		res;

	res = nb % 2;
	if (res > 0)
		return (1);
	return (0);
}

int		is_even(int nb)
{
	int		res;

	res = nb % 2;
	if (res < 0)
		return (1);
	return (0);
}

int		get_next_operator(char *line, int i)
{
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			sq++;
		else if (line[i] == '\"')
			dq++;
		else if (which_operator(line, i) > 0 && ((sq == 0 && dq == 0) || (is_even(sq) && is_even(dq))))
			return (i);
		i++;
	}
	return (i);
}

int		syntax_err_msg(char token)
{
	write(2, "bash: syntax error near unexpected token '", 43);
	if (token == '\0')
		write(2, "newline", 7);
	else
		write(2, &token, 1);
	write(1, "'\n", 2);
	return (0);
}

int		quotes_check(char *line)
{
	int		i;
	int		sq;
	int		dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			sq++;
		else if (line[i] == '\"')
			dq++;
		i++;
	}
	if (is_odd(sq) || is_odd(dq))
	{
		write(2, "bash: invalid quotes number, multiple lines are not supported\n", 62);
		return (0);
	}
	return (1);
}

int		operator_check(char *line)
{
	int		i;
	int		op;
	
	i = 0;
	op = 0;
	skip_spaces(line, &i);
	if (line[i] == '|' || line[i] == ';')
		return (syntax_err_msg(line[i]));
	while (1)
	{
		i = get_next_operator(line, i);
		if (line[i] == '\0')
			break;
		else
		{
			op = which_operator(line, i);
			i++;
			skip_spaces(line, &i);
			if ((line[i] == '|' || line[i] == ';') || (line[i] == '\0' && op > 1) ||
			((line[i] == '>' || line[i] == '<') && op > 2))
				return (syntax_err_msg(line[i]));
		}
	}
	return (1);
}

int		syntax_error_check(char *line)
{
	if (!quotes_check(line) || !operator_check(line))
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	(void)ac;
	if (syntax_error_check(av[1]))
		write(1, "syntax OK\n", 10);
	return (0);
}
