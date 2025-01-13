/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnumber_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:59:58 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/07 10:21:00 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	dget_digit(unsigned long long n, int *digit, int base)
{
	*digit = 1;
	while (n >= (unsigned int)base)
	{
		n /= base;
		(*digit)++;
	}
}

char	dget_place_num(unsigned long long n, int digit, int base)
{
	while (digit--)
		n /= base;
	n %= base;
	return (n & 0x0f);
}

void	dremove_place_num(unsigned long long *n, int digit, int base)
{
	int					i;
	unsigned long long	minus;

	if (digit == 1)
		*n = 0;
	else
	{
		i = 1;
		minus = base;
		while (i < (digit - 1))
		{
			minus *= base;
			i++;
		}
		minus *= dget_place_num(*n, digit - 1, base);
		*n -= minus;
	}
}

int	ft_dputnumber_check(int fd, unsigned long long n, t_form form, int *count)
{
	int	digit;

	dget_digit(n, &digit, form.base);
	while (digit)
	{
		ft_dputnum_check(fd, dget_place_num(n, digit - 1, form.base), form.fmt,
			count);
		if (*count == -1)
			return (*count);
		dremove_place_num(&n, digit, form.base);
		digit--;
	}
	return (*count);
}
