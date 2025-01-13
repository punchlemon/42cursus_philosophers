/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputhex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:20:07 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/07 10:15:07 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputhex_check(int fd, unsigned int n, char format, int *count)
{
	t_form	f;

	f.fmt = format;
	f.base = 16;
	return (ft_dputnumber_check(fd, (unsigned long long)n, f, count));
}
