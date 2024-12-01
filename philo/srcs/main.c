/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:06 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/01 12:09:37 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, const char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 5)
		data->num_of_times_each_philo_must_eat = 0;
	else
		data->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
}

int	main(const int argc, const char **argv)
{
	int		ret;
	t_data	data;
	t_philo	*philos;
	t_fork	*forks;

	ret = 0;
	(void)argv;
	if (argc > 4)
	{
		init_data(&data, argc, argv);
		// deb_print_data(data);
		if (run(&ret, data, &philos, &forks))
		{
		}
	}
	else
		return (ft_putendl_fd(2, "Error"), 1);
	destroy(data.num_of_philos, philos, forks);
	return (ret);
}
