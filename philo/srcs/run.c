/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/03 16:12:32 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(int *ret, int num_of_forks, t_fork **forks)
{
	int		i;

	*ret = 0;
	i = 0;
	*forks = malloc(sizeof(t_fork) * num_of_forks);
	if (*forks == NULL)
		return (*ret = 1, *ret);
	while (i < num_of_forks)
	{
		*ret = pthread_mutex_init(&((*forks)[i]), NULL);
		if (*ret != 0)
			return (*ret);
		i++;
	}
	return (0);
}

void	set_philo(t_philo *philos, int i, t_data d, t_fork *forks)
{
	t_philo	*p;

	p = &(philos[i]);
	p->born = FIRST;
	p->die = ALIVE;
	p->i = i;
	p->d = d;
	p->time_to_eat = d.time_to_eat;
	p->time_to_eat = d.time_to_sleep;
	p->delta_delay_time = p->time_to_eat * (2 / (p->d.num_of_philos - 1));
	p->odd_delay_time = p->time_to_eat + p->delta_delay_time;
	if (d.time_to_sleep >= d.time_to_die)
	{
		p->die = SLEEPING_DIE;
		p->time_to_sleep = d.time_to_die;
	}
	else
		p->time_to_sleep = d.time_to_sleep;
	p->left_fork = &(forks[i]);
	if (d.num_of_philos == 1)
		p->right_fork = NULL;
	else if (i == 0)
		p->right_fork = &(forks[d.num_of_philos - 1]);
	else
		p->right_fork = &forks[i - 1];
}

int	create_philos(int *ret, t_data d, t_philo **ps_p, t_fork *forks)
{
	int		i;

	*ret = 0;
	*ps_p = malloc(sizeof(t_philo) * d.num_of_philos);
	if (*ps_p == NULL)
		return (*ret = 1, *ret);
	i = 0;
	while (i < d.num_of_philos)
	{
		set_philo(*ps_p, i, d, forks);
		*ret = pthread_create(&((*ps_p)[i].tid), NULL, philo_life, &((*ps_p)[i]));
		if (*ret != 0)
			return (*ret);
		i++;
	}
	return (*ret);
}

int	wait_philos(int *ret, int num_of_philos, t_philo *philos)
{
	int	i;

	*ret = 0;
	i = 0;
	while (i < num_of_philos)
	{
		*ret = pthread_join(philos[i].tid, NULL);
		if (*ret != 0)
			return (*ret);
		i++;
	}
	return (*ret);
}

int	run(int *ret, t_data d, t_philo **philos, t_fork **forks)
{
	if (create_forks(ret, d.num_of_philos, forks) != 0)
		return (*ret);
	if (create_philos(ret, d, philos, *forks) != 0)
		return (*ret);
	if (wait_philos(ret, d.num_of_philos, *philos) != 0)
		return (*ret);
	return (*ret);
}
