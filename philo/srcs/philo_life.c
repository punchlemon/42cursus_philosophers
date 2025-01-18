/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/18 14:33:29 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo_life(t_philo *p)
{
	long	time;

	pthread_mutex_lock(&p->first_fork->mutex);
	time = get_time();
	printf("%ld %ld is thinking\n", time, p->id);
	time = get_time();
	printf("%ld %ld has taken a fork\n", time, p->id);
	pthread_mutex_unlock(&p->first_fork->mutex);
	p->dead_time = time + p->d.time_to_die;
	my_sleep(p->dead_time, p);
	p->is_dead = true;
}

long	philo_life_init(t_philo *p)
{
	long	time;

	if (p->d.num_of_philos == 1)
		return (single_philo_life(p), FAILURE);
	if (p->id == p->d.num_of_philos)
	{
		time = get_time() + 20;
		set_mutex_value(&p->pvals[START_ID], time);
	}
	else
	{
		while (true)
		{
			time = get_mutex_value(&p->pvals[START_ID]);
			if (time == FAILURE)
				usleep(500);
			else
				break ;
		}
	}
	p->dead_time = time + p->d.time_to_die;
	if (my_sleep(time, p) == FAILURE)
		return (FAILURE);
	return (time);
}

int	philo_spent_time(t_philo *p, const char *str, long time)
{
	long	now;

	now = print_with_timestamp_safe(p, str);
	if (now == FAILURE)
		return (FAILURE);
	if (my_sleep(now + time, p) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	*philo_life(void *arg)
{
	t_philo	*p;
	long	start_time;

	p = (t_philo *)arg;
	start_time = philo_life_init(p);
	if (start_time == FAILURE)
		return (NULL);
	print_with_timestamp_safe(p, "is thinking");
	if (my_sleep(start_time + p->time_to_first_think, p) == FAILURE)
		return (NULL);
	while (true)
	{
		if (p->d.argc == ARGC_MAX && p->d.num_of_times_to_eat == 0)
			return (NULL);
		if (philo_eat(p) == FAILURE)
			return (NULL);
		if (philo_spent_time(p, "is sleeping", p->d.time_to_sleep) == FAILURE)
			return (NULL);
		if (philo_spent_time(p, "is thinking", p->d.time_to_think) == FAILURE)
			return (NULL);
	}
	return (NULL);
}
