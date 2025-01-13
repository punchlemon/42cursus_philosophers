/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:48:16 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/13 16:54:31 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_sleep(long goal, t_philo *p)
{
	long	now;
	long	value;

	while (true)
	{
		value = get_mutex_value(&p->pvals[STATUS_ID]);
		if (value == THREAD_HALTED)
			return (FAILURE);
		now = get_time();
		if (p->dead_time < now)
		{
			pthread_mutex_lock(&p->pvals[STATUS_ID].mutex);
			if (p->pvals[STATUS_ID].value != THREAD_HALTED)
			{
				p->pvals[STATUS_ID].value = THREAD_HALTED;
				p->is_dead = true;
			}
			pthread_mutex_unlock(&p->pvals[STATUS_ID].mutex);
			return (FAILURE);
		}
		if (goal <= now)
			break ;
		usleep(500);
	}
	return (SUCCESS);
}
