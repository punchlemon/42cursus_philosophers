/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:51 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/18 15:18:06 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(int num_of_forks, t_fork **forks_p)
{
	int		i;
	t_fork	*forks;

	*forks_p = malloc(sizeof(t_fork) * num_of_forks);
	if (*forks_p == NULL)
		return (func_abort("malloc", "forks creation failed"));
	forks = *forks_p;
	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&forks[i].mutex);
			free(forks);
			return (func_abort("pthread_mutex", "forks creation failed"));
		}
		forks[i].value = 0;
		i++;
	}
	return (SUCCESS);
}

void	set_philo(t_philo *p, long i, t_data data, t_fork *forks)
{
	float	delta_delay_time;

	p->id = i + 1;
	p->d = data;
	p->is_dead = false;
	delta_delay_time = 0;
	if (p->d.num_of_philos != 1 && p->d.num_of_philos % 2)
		delta_delay_time = p->d.time_to_eat * 2.0 / (p->d.num_of_philos - 1);
	p->time_to_first_think = 0;
	if (i % 2)
		p->time_to_first_think += p->d.time_to_eat;
	p->time_to_first_think += (long)((p->id / 2) * delta_delay_time);
	p->d.time_to_think = p->d.time_to_eat - p->d.time_to_sleep
		+ (long)delta_delay_time;
	p->fst_fork = &(forks[i]);
	p->snd_fork = &(forks[i - 1]);
	if (i == 0)
		p->snd_fork = &(forks[data.num_of_philos - 1]);
	if (p->id % 2)
	{
		p->fst_fork = (void *)((size_t)p->fst_fork ^ (size_t)p->snd_fork);
		p->snd_fork = (void *)((size_t)p->fst_fork ^ (size_t)p->snd_fork);
		p->fst_fork = (void *)((size_t)p->fst_fork ^ (size_t)p->snd_fork);
	}
}

int	create_philos(t_data d, t_philo **philos_p, t_fork *forks, t_pval *pvals)
{
	long	i;
	t_philo	*philos;

	*philos_p = malloc(sizeof(t_philo) * d.num_of_philos);
	if (*philos_p == NULL)
		return (func_abort("malloc", "philos creation failed"));
	philos = *philos_p;
	i = 0;
	while (i < d.num_of_philos)
	{
		philos[i].pvals = pvals;
		set_philo(&philos[i], i, d, forks);
		if (pthread_create(&philos[i].tid, NULL, philo_life, &philos[i]) != 0)
		{
			set_mutex_value(&pvals[STATUS_ID], THREAD_HALTED);
			while (i--)
				pthread_join(philos[i].tid, NULL);
			free(philos);
			return (func_abort("pthread_create", "philos creation failed"));
		}
		i++;
	}
	return (SUCCESS);
}
