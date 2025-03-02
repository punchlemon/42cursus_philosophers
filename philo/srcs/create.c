/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:51 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/02 19:21:17 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philo(t_philo *p, long n, t_data data, t_resource *resources)
{
	int		i;

	p->id = n + 1;
	p->d = data;
	p->resources = resources;
	p->start_time = 0;
	p->dead_time = 0;
	if (p->id % 2)
		p->first_time_to_think = 0;
	else
		p->first_time_to_think = p->d.time_to_eat;
	if (p->d.num_of_philos != 1 && p->d.num_of_philos % 2)
		p->first_time_to_think += ((p->id / 2) * p->d.time_to_eat * 2)
			/ (p->d.num_of_philos - 1);
	i = 0;
	while (i < RESOURCES_LEN)
	{
		p->locked_resources[i] = false;
		i++;
	}
	p->count = 0;
	p->is_incompleted = (p->d.num_of_times_to_eat != 0);
}

int	create_philos(t_data d, pthread_t *tids, t_philo *philos,
	t_resource *resources)
{
	long	i;

	i = 0;
	while (i < d.num_of_philos)
	{
		set_philo(&philos[i], i, d, resources);
		if (pthread_create(&tids[i], NULL, start_philo_life, &philos[i]) != 0)
		{
			set_mutex_value(&philos[i], DIED_ID, NUM_OF_PHILOS_MAX + 1);
			while (i--)
				pthread_detach(tids[i]);
			return (destroy_mutexes(resources, RESOURCES_LEN),
				func_abort("philos creation failed", NULL));
		}
		i++;
	}
	return (SUCCESS);
}
