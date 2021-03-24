/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:45:30 by vlugand-          #+#    #+#             */
/*   Updated: 2021/03/17 12:32:43 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SYNTAXE CHECK IS JUST CALLED JUST ONCE FOR EACH LINE. UNLIKE THE PARSER IT WON'T BE CALLED BACK SINCE THE GIVEN LINE WILL BE EDITED
// CHECK IF LINE EXISTS BEFORE CALLING THESE FCT -- EMPTY LINES ACCEPTED BUT NO NULL LINES

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


int		ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int		ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*dst;
	size_t		i;
	size_t		size;

	if (!s)
		return (NULL);
	if (start + len > ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (len > size)
		len = size;
	if (!(dst = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[i + start];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && ((str[*i] > 8 && str[*i] < 14) || str[*i] == ' '))
		(*i)++;
}

int		which_operator(char *str, int i)
{
	if (str[i] == '\0')
		return (0);
	if (str[i] == ';')
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

char	*pipe_parsing(char *line)
{
	int		i;
	int		len;
	char	*tmp;
	char	*exec;

	i = 0;
	while (1)
	{
		i = get_next_operator(*line, i);
		if (which_operator(line, i) == 0)
			break ;
		i++;
	}
	tmp = ft_substr(line, 0, i); // we copy the string from 0 until the first " ; " || " \0 "
	len = ft_strlen(line + i + 1) + 1; // we get the len of line after the first " ; " || " \0 " and we add 1 to include the " \0 " || " ; "
	ft_memmove(line, line + i, len); // we move what is after the first " ; " to the beginning of line.
	exec = cmd_expansion(tmp); // expands env var if legit
	if (tmp)
		free(tmp);
	return (exec);
}

char	*semicolon_parsing(char *line) // prendre i en param??
{
	int			len;
	char		*exec;
	char		*tmp;

	tmp = ft_substr(*line, 0, i); // we copy the string from 0 until the first " ; "
	len = ft_strlen(*line + i + 1) + 1; // we get the len of line after the first " ; " and we add 1 to include the " \0 "
	ft_memmove(*line, *line + i, len); // we move what is after the first " ; " to the beginning of line.
	exec = cmd_expansion(tmp); // expands env var if legit
	if (tmp)
		free(tmp);
	return (exec);
}

int		is_env_var(char *line)
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
		else if (line[i] == '$' && ((sq == 0 && dq == 0) || (is_even(sq) && is_even(dq)))
		&& ft_isalpha(line[i + 1]))
			return (i);
		i++;
	}
	return (i);
}

char	*get_env_var(char *line)
{
	char	*env_var;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (line[len] || ft_isalnum(line[len]))
		len++;
	if (!(env_var = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		env_var[i] = line[i];
		i++;
	}
	env_var[len] = '\0';
	return (env_var);
}

char	*expand(char *env_var)
{
	int		i;
	int		len;
	
	i = 0;
	len = ft_strlen(env_var);
	while (g_shell->env)
	{
		if (ft_strncmp(g_shell->env->content, env_var, len) == 0 &&
		((char *)g_shell->env->content)[len] == '=')
		{
			free(env_var);
			env_var = ft_strdup(g_shell->env->content + (len + 1));
			return (env_var);
		}
		g_shell->env = g_shell->env->next;
	}
	return (NULL);
}


char	*merge_line(char *s1, char *s2, char *s3, int total_len)
{
	char	*new_line;
	int		i;
	int		j;

	if (!(new_line = malloc(sizeof(char) * (total_len + 1))))
		return (NULL);
	i = -1;
	while (s1[i++])
		new_line[i] = s1[i];
	j = 0;
	while (s2[i])
	{
		new_line[i] = s2[j];
		i++;
		j++;
	}
	j = 0;
	while (s3[i])
	{
		new_line[i] = s3[j];
		i++;
		j++;
	}
	new_line[i] = '\0';
	return (new_line);
}

void	trim_line(int var_len, int var_start, char **line, char *env_var)
{
	char	*tmp1;
	char	*tmp2;
	int		total_len;

	if (!(tmp1 = malloc(sizeof(char) * (var_start + 1))))
		return (NULL);
	ft_strlcpy(tmp1, line, var_start + 1);
	if (!(tmp2 = ft_strdup(line + var_start + var_len)))
		return (NULL);
	free(*line);
	total_len = ft_strlen(tmp1) + ft_strlen(env_var) + ft_strlen (tmp2);
	*line = merge_line(tmp1, env_var, tmp2, total_len);
	free(tmp1);
	free(tmp2);
}

char	*cmd_expansion(char *line)
{
	int		i;
	int		len;
	char	*env_var;
	char	*tmp;

	i = 0;
	if (!is_env_var(line))
		return (line);
	while (1)
	{
		i = is_env_var(line + i);
		env_var = get_env_var(line + i + 1);
		len = ft_strlen(env_var) + 1; // +1 for the $
		env_var = expand(env_var);
		trim_line(len, i, &line, env_var);
	
		i = 0;
	}
	
}

void	*parsing(char *line)
{
	int			i;
	char		*exec;
	t_cmdinfo	cmdinfo; // malloc cmdinfo
	
	
	i = get_next_operator(*line, 0); // stops after the first **legit** " | " or " ; " is found and returns its index or the index of the end of line if none found.
	if (line[i] = '|')
		exec = pipe_parsing(line); // on va recup toutes les commandes pipées jusqu'à la fin de line ou " ; "
	else if (line[i] = ';')
		semicolon_parsing(line); // on va recup tout jusqu'au " ; "
	else // s'il s'agit d'une cmd sans sep
		exec = cmd_expansion(line); //expands env var if legit
	quotes_removal(exec);
	fill_struct(cmdinfo);

	g_shell->cmd = ft_lstnew(&cmdinfo);
	free(line);
	skip_spaces(line);
	if (line[0] = '\0')
		free(line);
}

//free cmd
