/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:20:07 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/07 10:16:21 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputptr_check(int fd, unsigned long long p, int *count)
{
	t_form	f;

	ft_dputstr_check(fd, "0x", count);
	if (*count == -1)
		return (*count);
	f.fmt = 'p';
	f.base = 16;
	ft_dputnumber_check(fd, p, f, count);
	return (*count);
}
