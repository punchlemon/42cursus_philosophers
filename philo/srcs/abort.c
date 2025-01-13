/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 22:54:44 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/13 12:20:18 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_dprintf.h"
#include "philo.h"

int	func_abort(const char *str1, const char *str2)
{
	ft_dprintf(STDERR_FILENO, "Error: %s: %s\n", str1, str2);
	return (FAILURE);
}

int	proc_abort(const char *str)
{
	ft_dprintf(STDERR_FILENO, "Error: %s\n", str);
	return (EXIT_FAILURE);
}
