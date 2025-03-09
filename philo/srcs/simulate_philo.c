/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/09 16:37:00 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_set_start_time(t_philo *p)
{
	if (p->id == p->d.num_of_philos)
	{
		p->start_time = philo_get_time(p) + 100;
		pthread_mutex_lock(&p->super->mutex);
		p->super->start_time = p->start_time;
		pthread_mutex_unlock(&p->super->mutex);
	}
	else
	{
		while (true)
		{
			usleep(NYQUIST_INTERVAL);
			pthread_mutex_lock(&p->super->mutex);
			p->start_time = p->super->start_time;
			pthread_mutex_unlock(&p->super->mutex);
			if (p->start_time != FAILURE)
				break ;
		}
	}
	p->dead_time = p->d.time2die;
	while (philo_get_time(p) < 0)
		usleep(NYQUIST_INTERVAL);
}

int	philo_think(t_philo *p)
{
	long	now;
	long	time2think;
	int		result;

	result = FAILURE;
	if (print_with_timestamp(p, "is thinking", &now) == SUCCESS)
	{
		p->last_log_time = now;
		if (p->count == 0)
			time2think = p->first_time2think;
		else
			time2think = p->time2think;
		if (my_msleep(time2think, p) == SUCCESS)
			result = SUCCESS;
		if (p->is_incompleted && p->count >= p->d.num_of_times2eat)
		{
			pthread_mutex_lock(&p->super->mutex);
			p->super->completed_philos_num++;
			p->is_incompleted = false;
			if (p->super->completed_philos_num == p->d.num_of_philos)
				p->super->is_dead = true;
			pthread_mutex_unlock(&p->super->mutex);
		}
	}
	return (result);
}

int	philo_eat(t_philo *p)
{
	long	now;
	int		result;

	pthread_mutex_lock(&p->fork1->mutex);
	print_with_timestamp(p, "has taken a fork", NULL);
	pthread_mutex_lock(&p->fork2->mutex);
	print_with_timestamp(p, "has taken a fork", NULL);
	result = FAILURE;
	if (print_with_timestamp(p, "is eating", &now) == SUCCESS)
	{
		p->last_log_time = now;
		p->dead_time = now + p->d.time2die;
		if (my_msleep(p->d.time2eat, p) == SUCCESS)
			result = SUCCESS;
	}
	pthread_mutex_unlock(&p->fork1->mutex);
	pthread_mutex_unlock(&p->fork2->mutex);
	return (result);
}

int	philo_sleep(t_philo *p)
{
	long	now;
	int		result;

	result = FAILURE;
	if (print_with_timestamp(p, "is sleeping", &now) == SUCCESS)
	{
		p->last_log_time = now;
		if (my_msleep(p->d.time2sleep, p) == SUCCESS)
			result = SUCCESS;
	}
	return (result);
}

void	*simulate_philo(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	_set_start_time(p);
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
