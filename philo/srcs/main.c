/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:06 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/09 23:11:00 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_flags(t_flags *f)
{
	f->died = ALIVE;
	f->start_time = -1;
	if (pthread_mutex_init(&(f->checkable), NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&(f->printable), NULL) != 0)
		return (pthread_mutex_destroy(&(f->checkable)), FAILURE);
	if (pthread_mutex_init(&(f->startable), NULL) != 0)
		return (pthread_mutex_destroy(&(f->checkable))
			, pthread_mutex_destroy(&(f->printable)), FAILURE);
	return (SUCCESS);
}

void	init_data(t_data *d, int argc, const char **argv)
{
	d->num_of_philos = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		d->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
}

void	wait_philos(int num_of_philos, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
}

int	main(const int argc, const char **argv)
{
	t_data	d;
	t_philo	*philos;
	t_fork	*forks;
	t_flags	flags;

	if (set_flags(&flags) == FAILURE)
		return (1);
	(void)argv;
	if (argc > 4)
	{
		init_data(&d, argc, argv);
		if (valid_data(argc, d) == FAILURE)
			return (1);
		if (run(d, &philos, &forks, &flags) == FAILURE)
			return (1);
		wait_philos(d.num_of_philos, philos);
	}
	else
		return (put_stderr("Error\n"), 1);
	destroy(d.num_of_philos, philos, forks);
	return (0);
}
