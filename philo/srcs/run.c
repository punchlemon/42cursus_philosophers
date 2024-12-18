/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/09 23:19:54 by retanaka         ###   ########.fr       */
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
		{
			while (i--)
				pthread_mutex_destroy(&((*forks)[i]));
			return (free(forks), FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

void	set_philo(t_philo *p, int i, t_data d, t_fork *forks)
{
	t_time	delta_delay_time;

	p->born = FIRST;
	p->die = ALIVE;
	p->num_of_philos = d.num_of_philos;
	p->time_to_eat = d.time_to_eat;
	p->time_to_sleep = d.time_to_sleep;
	p->time_to_die = d.time_to_die;
	p->num_of_times_each_philo_must_eat = d.num_of_times_each_philo_must_eat;
	p->argc = d.argc;
	if (p->num_of_philos % 2)
		delta_delay_time = p->time_to_eat * 2 / (p->num_of_philos - 1);
	else
		delta_delay_time = 0;
	p->time_to_first_think = 0;
	if (p->i % 2)
		p->time_to_first_think += p->time_to_eat;
	p->time_to_first_think += ((p->i + 1) / 2) * delta_delay_time;
	p->time_to_second_after_think = p->time_to_eat - p->time_to_sleep
		+ delta_delay_time;
	p->left_fork = &(forks[i]);
	if (i > 0)
		p->right_fork = &(forks[i - 1]);
	else
		p->right_fork = &(forks[d.num_of_philos - 1]);
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
		set_philo(p, i, d, forks);
		if (pthread_create(&(p->tid), NULL, philo_life, p) != 0)
		{
			pthread_mutex_lock(&(p->flags->checkable));
			p->flags->died = END;
			pthread_mutex_unlock(&(p->flags->checkable));
			while (i--)
				pthread_join((*ps_p)[i].tid, NULL);
			return (free(*ps_p), FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	run(t_data d, t_philo **philos, t_fork **forks, t_flags *flags)
{
	if (create_forks(d.num_of_philos, forks) == FAILURE)
		return (FAILURE);
	if (create_philos(d, philos, *forks, flags) == FAILURE)
		return (destroy_forks(d.num_of_philos, *forks), FAILURE);
	return (SUCCESS);
}
