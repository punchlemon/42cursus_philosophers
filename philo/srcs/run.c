/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/05 11:10:39 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(int num_of_forks, t_fork **forks)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	*forks = malloc(sizeof(t_fork) * num_of_forks);
	if (*forks == NULL)
		return (ret = 1, ret);
	while (i < num_of_forks)
	{
		ret = pthread_mutex_init(&((*forks)[i]), NULL);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (ret);
}

void	set_philo(t_philo *p, int i, t_data d, t_fork *forks)
{
	int	ret;

	ret = pthread_mutex_init(&(p->flags->checkable), NULL);
	if (ret != 0)
		return (ret);
	ret = pthread_mutex_init(&(p->flags->printable), NULL);
	if (ret != 0)
		return (pthread_mutex_destroy(&(p->flags->checkable)), ret);
	p->born = FIRST;
	p->die = ALIVE;
	p->num_of_philos = d.num_of_philos;
	p->time_to_eat = d.time_to_eat;
	p->time_to_sleep = d.time_to_sleep;
	p->time_to_die = d.time_to_die;
	p->num_of_times_each_philo_must_eat = d.num_of_times_each_philo_must_eat;
	p->delta_delay_time = p->time_to_eat * 2 / (p->num_of_philos - 1);
	p->time_to_sleep = d.time_to_sleep;
	if (d.num_of_philos > 1)
	{
		p->left_fork = &(forks[i]);
		if (i > 0)
			p->right_fork = &(forks[i - 1]);
		else
			p->right_fork = &(forks[d.num_of_philos - 1]);
	}
}

int	create_philos(t_data d, t_philo **ps_p, t_fork *forks)
{
	int		i;
	int		ret;
	t_philo	*p;
	t_flags	flags;

	ret = 0;
	*ps_p = malloc(sizeof(t_philo) * d.num_of_philos);
	if (*ps_p == NULL)
		return (ret = 1, ret);
	i = 0;
	while (i < d.num_of_philos)
	{
		p = &((*ps_p)[i]);
		p->i = i;
		p->flags = &flags;
		set_philo(p, i, d, forks);
		ret = pthread_create(&(p->tid), NULL, philo_life, p);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (ret);
}

int	wait_philos(int num_of_philos, t_philo *philos)
{
	int		i;
	int		ret;

	i = 0;
	while (i < num_of_philos)
	{
		ret = pthread_join(philos[i].tid, NULL);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (ret);
}

int	run(t_data d, t_philo **philos, t_fork **forks)
{
	int	ret;

	ret = create_forks(d.num_of_philos, forks);
	if (ret != 0)
		return (ret);
	ret = create_philos(d, philos, *forks);
	if (ret != 0)
		return (ret);
	ret = wait_philos(d.num_of_philos, *philos);
	return (ret);
}
