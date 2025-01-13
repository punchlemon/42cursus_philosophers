/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:53:02 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/07 10:00:43 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputchar(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_dputstr(int fd, char *s)
{
	size_t	i;

	if (s == NULL)
		return (write(fd, "(null)", 6));
	i = -1;
	while (*(s + ++i) != '\0')
		;
	return (write(fd, s, i));
}
