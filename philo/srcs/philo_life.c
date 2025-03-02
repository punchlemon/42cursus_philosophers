/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/02 18:52:47 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	philo_life_init(t_philo *p, long *start_time_p)
{
	long	now;

	if (p->id == p->d.num_of_philos)
	{
		*start_time_p = get_time() + 20;
		set_mutex_value(p, START_ID, *start_time_p);
	}
	else
	{
		while (true)
		{
			usleep(NYQUIST_INTERVAL);
			if (get_mutex_value(p, START_ID, start_time_p) != FAILURE)
				break ;
		}
	}
	p->dead_time = *start_time_p + p->d.time_to_die;
	now = get_time();
	while (*start_time_p > now)
	{
		usleep(NYQUIST_INTERVAL);
		now = get_time();
	}
	return (*start_time_p);
}

int	philo_think(t_philo *p)
{
	long	now;

	if (print_with_timestamp(p, "is thinking", &now) == FAILURE)
		return (FAILURE);
	if (p->count == 0)
	{
		if (my_msleep(now, p->first_time_to_think, p) == FAILURE)
			return (FAILURE);
	}
	else if (p->d.num_of_times_to_eat != 0
		&& p->count >= p->d.num_of_times_to_eat)
		return (FAILURE);
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
	long	start_time;

	p = (t_philo *)arg;
	if (philo_life_init(p, &start_time) == FAILURE)
		return (NULL);
	while (true)
	{
		if (philo_think(p) == FAILURE)
			return (NULL);
		if (philo_eat(p) == FAILURE)
			return (NULL);
		if (philo_sleep(p) == FAILURE)
			return (NULL);
	}
	return (NULL);
}
