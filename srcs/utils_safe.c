/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:33:39 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/25 17:22:36 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isprint_safe(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

size_t	ft_strlen_safe(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_safe(const char *src)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * (ft_strlen_safe(src) + 1));
	if (dst == NULL)
		return (NULL);
	if (src != NULL)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (dst);
}
