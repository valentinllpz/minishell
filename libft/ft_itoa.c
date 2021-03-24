/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:34:47 by vlugand-          #+#    #+#             */
/*   Updated: 2019/11/15 13:35:26 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	int		i;
	char	*itoa;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = ft_intlen(n);
	if (!(itoa = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	if (n < 0)
	{
		n = -n;
		itoa[0] = '-';
	}
	itoa[i] = '\0';
	i--;
	while (n > 0)
	{
		itoa[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (itoa);
}
