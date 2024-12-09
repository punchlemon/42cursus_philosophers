/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:08:17 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/09 23:08:34 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_time_to(int time, const char *src)
{
	if (time > 100000)
	{
		put_stderr("too much ");
		put_stderr(src);
		write(2, "\n", 1);
		return (FAILURE);
	}
	else if (time < 10)
	{
		put_stderr("too little ");
		put_stderr(src);
		write(2, "\n", 1);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	valid_data(int argc, t_data d)
{
	if (d.num_of_philos > 200)
		return (put_stderr("too many num_of_philos\n"), FAILURE);
	else if (d.num_of_philos < 1)
		return (put_stderr("too few num_of_philos\n"), FAILURE);
	else if (valid_time_to(d.time_to_die, "time_to_die") == FAILURE)
		return (FAILURE);
	else if (valid_time_to(d.time_to_eat, "time_to_eat") == FAILURE)
		return (FAILURE);
	else if (valid_time_to(d.time_to_sleep, "time_to_sleep") == FAILURE)
		return (FAILURE);
	else if (d.num_of_philos == 1)
	{
		printf("%ld 1 is thinking\n", get_time());
		usleep(d.time_to_die);
		printf("%ld 1 dead\n", get_time());
		return (usleep(d.time_to_die), FAILURE);
	}
	else if (argc > 5 && d.num_of_times_each_philo_must_eat <= 0)
		return (put_stderr("too few num_of_times_each_philo_must_eat\n")
			, FAILURE);
	return (SUCCESS);
}
