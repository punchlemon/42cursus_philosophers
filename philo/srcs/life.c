/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/06 21:41:58 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	void	*retval;
	t_philo	*p;

	(void)retval;
	p = (t_philo *)arg;
	if (p->i == 0)
	{
		pthread_mutex_lock(&p->flags->startable);
		p->start = get_time();
		pthread_mutex_unlock(&p->flags->startable);
	}


	while (1)
	{
		philo_think(p);
		if (p->die == DEAD || p->die == END)
			return ((void *)0);
	}
	return ((void *)0); // Cant reachable
}
