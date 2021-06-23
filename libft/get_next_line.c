/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:19 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/23 14:41:10 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	recursive(char **line, size_t index, int fd)
{
	char	buf;
	int		ret;

	ret = read(fd, &buf, 1);
	if (ret == 1 && buf != '\n')
	{
		ret = recursive(line, index + 1, fd);
		if (ret != -1)
			(*line)[index] = buf;
	}
	else if (ret != -1)
	{
		*line = (char *)malloc(sizeof(char) * (index + 1));
		if (*line != NULL)
			(*line)[index] = '\0';
		else
			ret = -1;
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	return (recursive(line, 0, fd));
}
