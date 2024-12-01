/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/01 11:22:43 by retanaka         ###   ########.fr       */
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

int	create_philos(int *ret, t_data data, t_philo **philos, t_fork *forks)
{
	int		i;
	t_philo	*philo;

	*ret = 0;
	i = 0;
	*philos = malloc(sizeof(t_philo) * data.num_of_philos);
	if (*philos == NULL)
		return (*ret = 1, *ret);
	while (i < data.num_of_philos)
	{
		philo = &((*philos)[i]);
		philo->i = i;
		philo->data = data;
		philo->left_fork = &(forks[i]);
		if (i == 0)
			philo->right_fork = &(forks[data.num_of_philos - 1]);
		else
			philo->right_fork = &forks[i - 1];
		*ret = pthread_create(&(philo->tid), NULL, philo_life, (void *)philo);
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

int	run(int *ret, t_data data, t_philo **philos, t_fork **forks)
{
	if (create_forks(ret, data.num_of_philos, forks) != 0)
		return (*ret);
	if (create_philos(ret, data, philos, *forks) != 0)
		return (*ret);
	if (wait_philos(ret, data.num_of_philos, *philos) != 0)
		return (*ret);
	return (*ret);
}
