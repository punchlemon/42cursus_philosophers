/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputdec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:20:07 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/07 10:14:33 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputdec_check(int fd, int n, char format, int *count)
{
	unsigned long long	u_n;
	t_form	f;

	if (n < 0 && format != 'u')
	{
		if ((long long)n == -2147483648)
		{
			ft_dputstr_check(fd, "-2147483648", count);
			return (*count);
		}
		ft_dputchar_check(fd, '-', count);
		n = -n;
		if (*count == -1)
			return (*count);
	}
	u_n = (unsigned long long)n & 0xffffffff;
	f.fmt = format;
	f.base = 10;
	return (ft_dputnumber_check(fd, u_n, f, count));
}
