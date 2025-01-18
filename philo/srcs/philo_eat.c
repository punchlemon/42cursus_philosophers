/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:58:42 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/18 14:29:39 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_fork(t_philo *p)
{
	long	value;

	value = get_mutex_value(p->first_fork);
	if (value == p->id)
		return (FAILURE);
	value = get_mutex_value(p->second_fork);
	if (value == p->id)
		return (FAILURE);
	return (SUCCESS);
}

void	release_fork(t_philo *p)
{
	pthread_mutex_unlock(&p->first_fork->mutex);
	pthread_mutex_unlock(&p->second_fork->mutex);
}

void	get_fork(t_philo *p)
{
	pthread_mutex_lock(&p->first_fork->mutex);
	p->first_fork->value = p->id;
	print_with_timestamp_safe(p, "has taken a fork");
	pthread_mutex_lock(&p->second_fork->mutex);
	p->second_fork->value = p->id;
	print_with_timestamp_safe(p, "has taken a fork");
}

int	philo_eat(t_philo *p)
{
	int		ret;
	long	now;

	ret = FAILURE;
	while (check_fork(p) == FAILURE)
		usleep(500);
	get_fork(p);
	now = print_with_timestamp_safe(p, "is eating");
	if (now == FAILURE)
		return (release_fork(p), FAILURE);
	p->dead_time = now + p->d.time_to_die;
	ret = my_sleep(now + p->d.time_to_eat, p);
	release_fork(p);
	if (ret == FAILURE)
		return (FAILURE);
	if (p->d.argc == ARGC_MAX)
		p->d.num_of_times_to_eat--;
	return (SUCCESS);
}
