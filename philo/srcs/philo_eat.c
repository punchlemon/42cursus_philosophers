/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:58:44 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/02 18:28:57 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_pick_up_fork(t_philo *p, int fork)
{
	while (true)
	{
		if (priority_mutex_lock(p, fork) == FAILURE)
			return ((void)func_abort("Can't lock fork", NULL));
		if (p->resources[fork].value != p->id)
		{
			p->resources[fork].value = p->id;
			break ;
		}
		priority_mutex_unlock(p, fork);
		usleep(NYQUIST_INTERVAL);
	}
	print_with_timestamp(p, "has taken a fork", NULL);
}

static void	_put_down_forks(t_philo *p, int fork1, int fork2)
{
	priority_mutex_unlock(p, fork1);
	priority_mutex_unlock(p, fork2);
}

int	philo_eat(t_philo *p)
{
	long	now;
	int		fork1;
	int		fork2;
	int		tmp;

	fork1 = p->id;
	fork2 = (p->id % p->d.num_of_philos) + 1;
	if (fork1 > fork2)
	{
		tmp = fork1;
		fork1 = fork2;
		fork2 = tmp;
	}
	_pick_up_fork(p, fork1);
	_pick_up_fork(p, fork2);
	if (print_with_timestamp(p, "is eating", &now) == FAILURE)
		return (_put_down_forks(p, fork1, fork2), FAILURE);
	p->dead_time = now + p->d.time_to_die;
	if (my_msleep(now, p->d.time_to_eat, p) == FAILURE)
		return (_put_down_forks(p, fork1, fork2), FAILURE);
	_put_down_forks(p, fork1, fork2);
	p->count++;
	return (SUCCESS);
}
