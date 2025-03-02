/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 22:54:44 by retanaka          #+#    #+#             */
/*   Updated: 2025/02/21 18:41:20 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "philo.h"

int	func_abort(const char *str1, const char *str2)
{
	if (str2 == NULL)
		ft_dprintf(STDERR_FILENO, "Error: %s\n", str1);
	else
		ft_dprintf(STDERR_FILENO, "Error: %s: %s\n", str1, str2);
	return (FAILURE);
}
