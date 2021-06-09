/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:19 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/09 12:27:35 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*join_and_free(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*dst;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(dst = (char*)malloc((len1 + len2 + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	free(s1);
	s1 = NULL;
	i = -1;
	while (s2[++i])
		dst[len1 + i] = s2[i];
	dst[len1 + i] = '\0';
	return (dst);
}

static int		find_index(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] != (char)c)
		return (-1);
	return (i);
}

static int		get_line(char *str, char **line, int i)
{
	int		len;

	*line = ft_substr(str, 0, i);
	++i;
	len = ft_strlen(str + i) + 1;
	ft_memmove(str, str + i, len);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char			buff[8];
	static char		*str = NULL;
	int				ret;
	int				i;

	if (!line || fd < 0 || read(fd, buff, 0) < 0)
		return (-1);
	if (str && (((i = find_index(str, '\n')) != -1)))
		return (get_line(str, line, i));
	while (((ret = read(fd, buff, 7)) > 0))
	{
		buff[ret] = '\0';
		str = join_and_free(str, buff);
		if (((i = find_index(str, '\n')) != -1))
			return (get_line(str, line, i));
	}
	if (str)
	{
		*line = ft_strdup(str);
		free(str);
		str = NULL;
		return (ret);
	}
	*line = ft_strdup("");
	return (ret);
}
