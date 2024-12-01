/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:14:57 by retanaka          #+#    #+#             */
/*   Updated: 2024/11/27 13:07:30 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_fd(const int fd, const char *src)
{
	return (write(fd, src, ft_strlen(src)));
}

int	ft_putchar_fd(const int fd, const char c)
{
	return (write(fd, &c, 1));
}

int	ft_putendl_fd(const int fd, const char *src)
{
	int	len;

	len = ft_put_fd(fd, src);
	if (len == -1)
		return (-1);
	if (ft_putchar_fd(fd, '\n') == -1)
		return (-1);
	return (len + 1);
}
