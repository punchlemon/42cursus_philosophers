/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 08:16:58 by retanaka          #+#    #+#             */
/*   Updated: 2025/02/21 19:07:09 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_mutex_value(t_philo *p, int id, long value)
{
	if (priority_mutex_lock(p, id) == FAILURE)
		return (FAILURE);
	p->resources[id].value = value;
	priority_mutex_unlock(p, id);
	return (SUCCESS);
}

int	get_mutex_value(t_philo *p, int id, long *value_p)
{
	if (priority_mutex_lock(p, id) == FAILURE)
		return (FAILURE);
	*value_p = p->resources[id].value;
	priority_mutex_unlock(p, id);
	return (SUCCESS);
}

int	priority_mutex_lock(t_philo *p, int id)
{
	int	last_resource_id;
	int	i;

	last_resource_id = 0;
	i = 0;
	while (i < RESOURCES_LEN)
	{
		if (p->locked_resources[i])
			last_resource_id = i;
		i++;
	}
	if (last_resource_id >= id)
		return (FAILURE);
	p->locked_resources[id] = true;
	pthread_mutex_lock(&p->resources[id].mutex);
	return (SUCCESS);
}

void	priority_mutex_unlock(t_philo *p, int id)
{
	p->locked_resources[id] = false;
	pthread_mutex_unlock(&p->resources[id].mutex);
}

void	destroy_mutexes(t_resource *resources, int i)
{
	while (i)
		pthread_mutex_destroy(&resources[--i].mutex);
}
