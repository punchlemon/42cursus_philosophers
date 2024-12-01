/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:10:31 by retanaka          #+#    #+#             */
/*   Updated: 2024/11/27 14:07:07 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#define THRESHOLD 214748364

int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	num = 0;
	while (ft_isdigit(*str))
	{
		if (sign == 1
			&& (num > THRESHOLD || (num == THRESHOLD && *str >= '7')))
			return (INT_MAX);
		if (sign == -1
			&& (num > THRESHOLD || (num == THRESHOLD && *str >= '8')))
			return (INT_MIN);
		num = num * 10 + *str - '0';
		str++;
	}
	return (num * sign);
}
