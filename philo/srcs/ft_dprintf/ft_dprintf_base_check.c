/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_base_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:09:01 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/07 09:56:46 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputchar_check(int fd, char s, int *count)
{
	if (ft_dputchar(fd, s) == -1)
		*count = -1;
	else
		(*count)++;
	return (*count);
}

int	ft_dputstr_check(int fd, char *s, int *count)
{
	int	len;

	len = ft_dputstr(fd, s);
	if (len == -1)
		*count = len;
	else
		*count += len;
	return (*count);
}

int	ft_dputnum_check(int fd, char n, char format, int *count)
{
	if (n < 10)
		n += '0';
	else if (n < 16 && format == 'X')
		n += ('A' - 10);
	else if (n < 16)
		n += ('a' - 10);
	else
		n = 0;
	ft_dputchar_check(fd, n, count);
	return (*count);
}
