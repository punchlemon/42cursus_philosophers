/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/02 19:36:48 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_philo_life_init(t_philo *p)
{
	long	now;

	if (p->id == p->d.num_of_philos)
	{
		p->start_time = get_time() + 20;
		set_mutex_value(p, START_ID, p->start_time);
	}
	else
	{
		while (true)
		{
			usleep(NYQUIST_INTERVAL);
			if (get_mutex_value(p, START_ID, &p->start_time) != FAILURE)
				break ;
		}
	}
	p->dead_time = p->start_time + p->d.time_to_die;
	now = get_time();
	while (p->start_time > now)
	{
		usleep(NYQUIST_INTERVAL);
		now = get_time();
	}
}

int	philo_think(t_philo *p)
{
	long	now;

	if (print_with_timestamp(p, "is thinking", &now) == FAILURE)
		return (FAILURE);
	if (p->count == 0)
	{
		if (my_msleep(p->start_time, p->first_time_to_think, p) == FAILURE)
			return (FAILURE);
	}
	else if (p->is_incompleted && p->count >= p->d.num_of_times_to_eat)
	{
		priority_mutex_lock(p, COMPLETED_ID);
		p->resources[COMPLETED_ID].value++;
		p->is_incompleted = false;
		if (p->resources[COMPLETED_ID].value == p->d.num_of_philos)
			set_died(p, false);
		priority_mutex_unlock(p, COMPLETED_ID);
	}
	return (SUCCESS);
}

int	philo_sleep(t_philo *p)
{
	long	now;

	if (print_with_timestamp(p, "is sleeping", &now) == FAILURE)
		return (FAILURE);
	if (my_msleep(now, p->d.time_to_sleep, p) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	*start_philo_life(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	_philo_life_init(p);
	if (p->start_time == FAILURE)
		return (NULL);
	while (true)
	{
		if (philo_think(p) == FAILURE)
			return (NULL);
		if (philo_eat(p) == FAILURE)
			return (NULL);
		if (philo_sleep(p) == FAILURE)
			return (NULL);
		if (p->is_incompleted)
			p->count++;
	}
	return (NULL);
}
