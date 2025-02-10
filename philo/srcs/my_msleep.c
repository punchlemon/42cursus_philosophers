/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:48:16 by retanaka          #+#    #+#             */
/*   Updated: 2025/02/10 17:58:02 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_thread_halted(t_philo *p)
{
	pthread_mutex_lock(&p->pvals[STATUS_ID].mutex);
	if (p->pvals[STATUS_ID].value != THREAD_HALTED)
	{
		p->pvals[STATUS_ID].value = THREAD_HALTED;
		p->is_dead = true;
	}
	pthread_mutex_unlock(&p->pvals[STATUS_ID].mutex);
}

int	my_msleep(long start, long msec, t_philo *p)
{
	long	goal;
	long	now;

	goal = start + msec;
	now = get_time();
	while (goal > now)
	{
		if (get_mutex_value(&p->pvals[STATUS_ID]) == THREAD_HALTED)
			return (FAILURE);
		if (p->dead_time < now)
			return (set_thread_halted(p), FAILURE);
		usleep(500);
		now = get_time();
	}
	return (SUCCESS);
}
