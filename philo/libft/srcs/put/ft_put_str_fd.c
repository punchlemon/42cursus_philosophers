/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_str_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:05:31 by retanaka          #+#    #+#             */
/*   Updated: 2024/11/27 13:08:46 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_str_fd(const int fd, const t_str str)
{
	return (write(fd, str.src, str.len));
}

int	ft_putendl_str_fd(const int fd, const t_str str)
{
	int	len;

	len = ft_put_str_fd(fd, str);
	if (len == -1)
		return (-1);
	if (ft_putchar_fd(fd, '\n') == -1)
		return (-1);
	return (len + 1);
}
