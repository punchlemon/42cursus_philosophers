/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2025/02/10 18:19:35 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	philo_life_init(t_philo *p)
{
	long	time;

	if (p->id == p->d.num_of_philos)
		set_mutex_value(&p->pvals[START_ID], get_time + 20);
	time = get_mutex_value(&p->pvals[START_ID]);
	while (time == FAILURE)
	{
		usleep(NYQUIST_INTERVAL);
		time = get_mutex_value(&p->pvals[START_ID]);
	}
	p->dead_time = time + p->d.time_to_die;
	if (my_msleep(get_time(), time, p) == FAILURE)
		return (FAILURE);
	return (time);
}

int	philo_spent_time(t_philo *p, const char *str, long time)
{
	long	now;

	now = print_with_timestamp_safe(p, str);
	if (now == FAILURE)
		return (FAILURE);
	if (my_msleep(now, time, p) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_and_lock_fork(t_philo *p, t_fork *fork)
{
	long	value;

	value = get_mutex_value(fork);
	if (value == p->id)
		return (FAILURE);
	set_mutex_value(fork, p->id);
	print_with_timestamp_safe(p, "has taken a fork");
	return (SUCCESS);
}

int	philo_eat(t_philo *p)
{
	int		ret;
	long	now;

	ret = FAILURE;
	while (check_and_lock_fork(p, p->fst_fork) == FAILURE)
		if (my_msleep(get_time(), 1, p) == FAILURE)
			return (FAILURE);
	while (check_and_lock_fork(p, p->snd_fork) == FAILURE)
		if (my_msleep(get_time(), 1, p) == FAILURE)
			return (FAILURE);
	now = print_with_timestamp_safe(p, "is eating");
	if (now == FAILURE)
		return (FAILURE);
	p->dead_time = now + p->d.time_to_die;
	ret = my_msleep(now, p->d.time_to_eat, p);
	if (ret == FAILURE)
		return (FAILURE);
	if (p->d.argc == ARGC_MAX)
		p->d.num_of_times_to_eat--;
	set_mutex_value(p->fst_fork, 0);
	set_mutex_value(p->snd_fork, 0);
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
	if (my_msleep(start_time, p->time_to_first_think, p) == FAILURE)
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
