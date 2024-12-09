/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:02:13 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/09 16:32:27 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *p)
{
	t_time	now;

	now = check_print_time(p, "is sleeping");
	if (now == FAILURE)
		return (FAILURE);
	if (my_sleep(now + p->time_to_sleep, p))
		return (FAILURE);
	p->last_move_time = now;
	return (SUCCESS);
}
