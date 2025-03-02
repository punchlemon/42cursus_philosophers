/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:06 by retanaka          #+#    #+#             */
/*   Updated: 2025/02/21 18:55:52 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_resources(t_resource *resources)
{
	int	i;

	i = 0;
	while (i < RESOURCES_LEN)
	{
		if (pthread_mutex_init(&resources[i].mutex, NULL) != 0)
			return (destroy_mutexes(resources, i),
				func_abort("mutex creation failure", NULL));
		resources[i].value = FAILURE;
		i++;
	}
	return (SUCCESS);
}

int	main(const int argc, const char **argv)
{
	int			i;
	t_data		d;
	pthread_t	tids[NUM_OF_PHILOS_MAX];
	t_philo		philos[NUM_OF_PHILOS_MAX];
	t_resource	resources[RESOURCES_LEN];

	if (process_input(&d, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (set_resources(resources) == FAILURE)
		return (EXIT_FAILURE);
	if (create_philos(d, tids, philos, resources) == FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (i < d.num_of_philos)
		pthread_join(tids[i++], NULL);
	destroy_mutexes(resources, RESOURCES_LEN);
	return (EXIT_SUCCESS);
}
