/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:03:47 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/07 14:03:54 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_first_think(t_philo *p)
{
	p->born = SECOND_AFTER;
	if (p->i == 0)
	{
		pthread_mutex_lock(&p->flags->startable);
		p->flags->start_time = get_time();
		p->start_time = p->flags->start_time;
		pthread_mutex_unlock(&p->flags->startable);
		p->dead_time = p->start_time + p->time_to_die;
	}
	else
	{
		while (1)
		{
			pthread_mutex_lock(&p->flags->startable);
			p->start_time = p->flags->start_time;
			pthread_mutex_unlock(&p->flags->startable);
			if (p->start_time != -1)
			{
				p->dead_time = p->start_time + p->time_to_die;
				break ;
			}
		}
	}
	return (my_sleep(p->start_time + p->time_to_first_think, p));
}

int	philo_think(t_philo *p)
{
	t_time	now;

	if (p->born == FIRST)
	{
		if (philo_first_think(p) == FAILURE)
			return (FAILURE);
	}
	else
	{
		now = check_print_time(p, "is thinking");
		if (now == FAILURE)
			return (FAILURE);
		if (my_sleep(p->last_move_time + p->time_to_second_after_think, p) == FAILURE)
			return (FAILURE);
		p->last_move_time = now;
	}
	return (SUCCESS);
}