/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:01:22 by retanaka          #+#    #+#             */
/*   Updated: 2024/11/28 16:13:31 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(int num_of_forks, t_fork *forks)
{
	int	i;

	i = 0;
	if (forks == NULL)
		return ;
	while (i < num_of_forks)
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
}

void	destroy(int num_of_forks, t_philo *philos, t_fork *forks)
{
	free(philos);
	destroy_forks(num_of_forks, forks);
	free(forks);
}
