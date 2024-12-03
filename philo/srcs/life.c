/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/03 13:59:38by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	print_time(int philo_i, const char *src)
{
	t_timeval	tv;
	t_time		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (src)
		printf("%ld %d %s\n", time, philo_i, src);
	return (time);
}

void	philo_sleep(t_philo *p)
{
	print_time(p->i, "is sleeping");
	usleep(p->time_to_sleep);
}

int	philo_eat(t_philo *p)
{
	p->last_eat_time = print_time(p->i, "is eating");
	usleep(p->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	philo_sleep(p);
	return (0);
}

int	philo_think(t_philo *p)
{
	t_time	now;
	int		time_to_think;

	now = print_time(p->i, "is thinking");
	time_to_think = 0;
	if (p->born == FIRST)
	{
		p->last_eat_time = now;
		p->born = SECOND_AFTER;
		if (p->d.num_of_philos % 2)
			time_to_think += ((p->i + 1) / 2) * p->delta_delay_time;
		if (p->i % 2)
			time_to_think += p->odd_delay_time;
	}
	else
		time_to_think = p->odd_delay_time - (now - p->last_eat_time);
	if (time_to_think > (now - p->last_eat_time + p->d.time_to_die)) // 考えてる間に死ぬ
	{
		p->die = THINKING_DIE;
		time_to_think = (now - p->last_eat_time + p->d.time_to_die);
	}
	usleep(time_to_think);
	if (p->die == THINKING_DIE)
		return (print_time(p->i, "is dead"), DEAD);
	while (1)
	{
		if (pthread_mutex_lock(p->left_fork) == 0)
		{
			print_time(p->i, "has taken a fork");
			if (pthread_mutex_lock(p->right_fork) == 0)
			{
				print_time(p->i, "has taken a fork");
				break ;
			}
		}
		usleep(1000);
	}
	philo_eat(p);
	if (p->die == SLEEPING_DIE)
		return (print_time(p->i, "is dead"), DEAD);
	return (ALIVE);
}

void	*philo_life(void *arg)
{
	void	*retval;
	t_philo	*p;

	(void)retval;
	p = (t_philo *)arg;
	while (1)
	{
		if (philo_think(p) == DEAD)
			return ((void *)DEAD);
	}
	return ((void *)0); // Cant reachable
}
