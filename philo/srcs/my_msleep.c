/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:48:16 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/09 19:14:28 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_died(t_philo *p, int is_print)
{
	pthread_mutex_lock(&p->super->mutex);
	if (!p->super->is_dead)
	{
		p->super->is_dead = true;
		if (is_print)
			printf("%ld %ld %s\n", philo_get_time(p), p->id, "died");
	}
	pthread_mutex_unlock(&p->super->mutex);
}

int	my_msleep(long msec, t_philo *p)
{
	long	limit;
	bool	will_die;

	will_die = ((p->last_log_time + msec) >= p->dead_time);
	if (will_die)
		limit = p->dead_time;
	else
	{
		p->last_log_time += msec;
		limit = p->last_log_time;
	}
	while (limit > philo_get_time(p))
	{
		pthread_mutex_lock(&p->super->mutex);
		if (p->super->is_dead)
			return (pthread_mutex_unlock(&p->super->mutex), FAILURE);
		pthread_mutex_unlock(&p->super->mutex);
		usleep(NYQUIST_INTERVAL);
	}
	if (will_die)
		return (set_died(p, true), FAILURE);
	return (SUCCESS);
}
