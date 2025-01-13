/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_check_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:08:17 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/13 14:30:24 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_data(t_data *d, int argc, const char **argv)
{
	d->num_of_philos = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	if (argc == ARGC_MAX)
		d->num_of_times_to_eat = ft_atoi(argv[5]);
	d->argc = argc;
}

int	check_data_time(int time, const char *str)
{
	if (time < TIME_VALUE_MIN)
		return (func_abort(str, "too little"));
	else if (time > TIME_VALUE_MAX)
		return (func_abort(str, "too much"));
	return (SUCCESS);
}

int	set_and_check_data(t_data *d, int argc, const char **argv)
{
	set_data(d, argc, argv);
	if (d->num_of_philos > NUM_OF_PHILO_MAX)
		return (func_abort("num_of_philos", "too many"));
	else if (d->num_of_philos < NUM_OF_PHILO_MIN)
		return (func_abort("num_of_philos", "too few"));
	else if (check_data_time(d->time_to_die, "time_to_die") == FAILURE
		|| check_data_time(d->time_to_eat, "time_to_eat") == FAILURE
		|| check_data_time(d->time_to_sleep, "time_to_sleep") == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
