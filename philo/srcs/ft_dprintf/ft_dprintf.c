/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:15:53 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/07 10:19:30 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputarg_check(int fd, char format, va_list *args, int *count)
{
	if (format == '%')
		ft_dputchar_check(fd, '%', count);
	if (format == 'c')
		ft_dputchar_check(fd, (char)va_arg(*args, int), count);
	if (format == 's')
		ft_dputstr_check(fd, (char *)va_arg(*args, char *), count);
	if (format == 'p')
		ft_dputptr_check(fd, (unsigned long long)va_arg(*args, void *), count);
	if (format == 'o')
		ft_dputoct_check(fd, va_arg(*args, int), count);
	if (format == 'u' || format == 'd' || format == 'i')
		ft_dputdec_check(fd, va_arg(*args, int), format, count);
	if (format == 'x' || format == 'X')
		ft_dputhex_check(fd, va_arg(*args, int), format, count);
	return (*count);
}

int	ft_dprintf(int fd, const char *source, ...)
{
	va_list	args;
	int		count;
	size_t	i;

	va_start(args, source);
	i = 0;
	count = 0;
	while (source[i])
	{
		if (source[i] == '%')
			ft_dputarg_check(fd, source[++i], &args, &count);
		else
			ft_dputchar_check(fd, source[i], &count);
		if (count == -1)
			break ;
		i++;
	}
	va_end(args);
	return (count);
}
