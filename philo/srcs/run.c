/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/05 15:36:59by retanaka         ###   ########.fr       */
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

int	set_philo(t_philo *p, int i, t_data d, t_fork *forks)
{
	int		ret;
	t_time	delta_delay_time;

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
	
	if (p->num_of_philos % 2)
		delta_delay_time = p->time_to_eat * 2 / (p->num_of_philos - 1);
	else
		delta_delay_time = 0;

	// １回目の思考時間
	p->time_to_first_think = 0;
	if (p->i % 2)
		p->time_to_first_think += p->time_to_eat;
	p->time_to_first_think += ((p->i + 1) / 2) * delta_delay_time;
	if (p->time_to_first_think > p->time_to_die)
	{
		p->die = THINKING_DIE;
		p->time_to_first_think = p->time_to_die;
	}
	else if (p->time_to_eat > p->time_to_die)
	{
		p->die = EATING_DIE;
		p->time_to_eat = p->time_to_die;
	}
	else if ((p->time_to_eat + p->time_to_sleep) > p->time_to_die)
	{
		p->die = SLEEPING_DIE;
		p->time_to_sleep = p->time_to_die - p->time_to_eat;
	}

	// ２回めの思考時間
	if (p->time_to_second_after_think + delta_delay_time > p->time_to_die - p->time_to_eat - p->time_to_sleep)
	{
		p->die = THINKING_DIE;
		p->time_to_first_think = p->time_to_die;
	}
	else
		p->time_to_second_after_think = p->time_to_eat - p->time_to_sleep + delta_delay_time;

	if (d.num_of_philos > 1)
	{
		p->left_fork = &(forks[i]);
		if (i > 0)
			p->right_fork = &(forks[i - 1]);
		else
			p->right_fork = &(forks[d.num_of_philos - 1]);
	}
	return (ret);
}

int	create_philos(t_data d, t_philo **ps_p, t_fork *forks, t_flags *flags)
{
	int		i;
	int		ret;
	t_philo	*p;

	ret = 0;
	*ps_p = malloc(sizeof(t_philo) * d.num_of_philos);
	if (*ps_p == NULL)
		return (ret = 1, ret);
	i = 0;
	while (i < d.num_of_philos)
	{
		p = &((*ps_p)[i]);
		p->i = i;
		p->flags = flags;
		ret = set_philo(p, i, d, forks);
		if (ret != 0)
			return (ret);
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
	int		ret;
	t_flags	flags;

	flags.died = 0; // init
	ret = create_forks(d.num_of_philos, forks);
	if (ret != 0)
		return (ret);
	ret = create_philos(d, philos, *forks, &flags);
	if (ret != 0)
		return (ret);
	ret = wait_philos(d.num_of_philos, *philos);
	return (ret);
}
