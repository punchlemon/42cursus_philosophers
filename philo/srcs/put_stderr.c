/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stderr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 22:54:44 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/09 22:56:32 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *src)
{
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	return (len);
}

int	put_stderr(const char *src)
{
	return (write(2, src, ft_strlen(src)));
}
