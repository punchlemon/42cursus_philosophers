/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:48:16 by retanaka          #+#    #+#             */
/*   Updated: 2025/02/18 16:42:32 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_died(t_philo *p)
{
	pthread_mutex_lock(&p->pvals[DIED_ID].mutex);
	if (p->pvals[DIED_ID].value == FAILURE)
		p->pvals[DIED_ID].value = p->id;
	pthread_mutex_unlock(&p->pvals[DIED_ID].mutex);
}

int	my_msleep(long start, long msec, t_philo *p)
{
	long	goal;
	long	now;

	goal = start + msec;
	now = get_time();
	while (goal > now)
	{
		if (get_mutex_value(&p->pvals[DIED_ID]) != FAILURE)
			return (FAILURE);
		if (p->dead_time < now)
			return (set_died(p), FAILURE);
		usleep(NYQUIST_INTERVAL);
		now = get_time();
	}
	return (SUCCESS);
}
