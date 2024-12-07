/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/07 13:42:37 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(int num_of_forks, t_fork **forks)
{
	int	i;

	*forks = malloc(sizeof(t_fork) * num_of_forks);
	if (*forks == NULL)
		return (FAILURE);
	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&((*forks)[i]), NULL) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	set_flags(t_flags *f)
{
	if (pthread_mutex_init(&(f->checkable), NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&(f->printable), NULL) != 0)
		return (pthread_mutex_destroy(&(f->checkable)), FAILURE);
	f->start_time = -1;
	f->died = ALIVE;
	return (SUCCESS);
}

int	set_philo(t_philo *p, int i, t_data d, t_fork *forks)
{
	t_time	delta_delay_time;

	p->born = FIRST;
	p->die = ALIVE;
	p->num_of_philos = d.num_of_philos;
	p->time_to_eat = d.time_to_eat;
	p->time_to_sleep = d.time_to_sleep;
	p->time_to_die = d.time_to_die;
	p->num_of_times_each_philo_must_eat = d.num_of_times_each_philo_must_eat;

	if (set_flags(p->flags) == FAILURE)
		return (FAILURE);
	
	if (p->num_of_philos % 2)
		delta_delay_time = p->time_to_eat * 2 / (p->num_of_philos - 1);
	else
		delta_delay_time = 0;

	// １回目の思考時間
	p->time_to_first_think = 0;
	if (p->i % 2)
		p->time_to_first_think += p->time_to_eat;
	p->time_to_first_think += ((p->i + 1) / 2) * delta_delay_time;

	// ２回めの思考時間
	p->time_to_second_after_think = p->time_to_eat - p->time_to_sleep + delta_delay_time;

	if (d.num_of_philos > 1)
	{
		p->left_fork = &(forks[i]);
		if (i > 0)
			p->right_fork = &(forks[i - 1]);
		else
			p->right_fork = &(forks[d.num_of_philos - 1]);
	}
	return (SUCCESS);
}

int	create_philos(t_data d, t_philo **ps_p, t_fork *forks, t_flags *flags)
{
	int		i;
	t_philo	*p;

	*ps_p = malloc(sizeof(t_philo) * d.num_of_philos);
	if (*ps_p == NULL)
		return (FAILURE);
	i = 0;
	while (i < d.num_of_philos)
	{
		p = &((*ps_p)[i]);
		p->i = i;
		p->flags = flags;
		if (set_philo(p, i, d, forks) == FAILURE)
			return (FAILURE);
		if (pthread_create(&(p->tid), NULL, philo_life, p) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	wait_philos(int num_of_philos, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_join(philos[i].tid, NULL) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	run(t_data d, t_philo **philos, t_fork **forks)
{
	t_flags	flags;

	flags.died = 0; // init
	if (create_forks(d.num_of_philos, forks) == FAILURE)
		return (FAILURE);
	if (create_philos(d, philos, *forks, &flags) == FAILURE)
		return (FAILURE);
	return (wait_philos(d.num_of_philos, *philos));
}
