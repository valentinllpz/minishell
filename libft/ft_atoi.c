/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:07:34 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/23 14:02:31 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int						i;
	int						sign;
	unsigned long long		res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && ((str[i] > 8 && str[i] < 14) || (str[i] == 32)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if ((i > 19 || res >= 9223372036854775808ULL) && sign == 1)
		return (-1);
	else if ((i > 19 || res >= 9223372036854775808ULL) && sign == -1)
		return (0);
	return (res * sign);
}
