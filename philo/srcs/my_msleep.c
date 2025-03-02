/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:48:16 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/02 19:12:19 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_died(t_philo *p)
{
	if (priority_mutex_lock(p, DIED_ID) == FAILURE)
		return ((void)func_abort("Can't lock DIED_ID", NULL));
	if (p->resources[DIED_ID].value == FAILURE)
	{
		p->resources[DIED_ID].value = p->id;
		if (priority_mutex_lock(p, PRINT_ID) == FAILURE)
			return ((void)func_abort("Can't lock PRINT_ID", NULL));
		printf("%ld %ld %s\n", get_time(), p->id, "died");
		priority_mutex_unlock(p, PRINT_ID);
	}
	priority_mutex_unlock(p, DIED_ID);
}

int	my_msleep(long start, long msec, t_philo *p)
{
	long	goal;
	long	now;
	long	died_id;

	goal = start + msec;
	now = get_time();
	while (goal > now)
	{
		if (get_mutex_value(p, DIED_ID, &died_id) == FAILURE)
			return (FAILURE);
		if (died_id != FAILURE)
			return (FAILURE);
		if (p->dead_time < now)
			return (set_died(p), FAILURE);
		usleep(NYQUIST_INTERVAL);
		now = get_time();
	}
	return (SUCCESS);
}
