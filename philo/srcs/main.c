/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:06 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/06 13:43:09 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *d, int argc, const char **argv)
{
	d->num_of_philos = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]) * 1000;
	d->time_to_eat = ft_atoi(argv[3]) * 1000;
	d->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 5)
		d->num_of_times_each_philo_must_eat = 0;
	else
		d->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
}

int	main(const int argc, const char **argv)
{
	int		ret;
	t_data	d;
	t_philo	*philos;
	t_fork	*forks;

	ret = 0;
	(void)argv;
	if (argc > 4)
	{
		init_data(&d, argc, argv);
		// deb_print_data(d);
		if (run(d, &philos, &forks))
		{
		}
	}
	else
		return (write(2, "Error\n", 6), 1);
	destroy(d.num_of_philos, philos, forks);
	return (ret);
}
