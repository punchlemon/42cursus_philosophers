/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:53:40 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/06 13:43:54 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_iswhitespace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	while (ft_iswhitespace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	num = 0;
	while ('0' <= *str && *str <= '9')
	{
		if (sign == 1
			&& (num > INT_MAX / 10 || (num == INT_MAX / 10 && *str >= '7')))
			return (INT_MAX);
		if (sign == -1
			&& (num > INT_MAX / 10 || (num == INT_MAX / 10 && *str >= '8')))
			return (INT_MIN);
		num = num * 10 + *str - '0';
		str++;
	}
	return (num * sign);
}
