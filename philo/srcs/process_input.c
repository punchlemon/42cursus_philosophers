/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:08:17 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/09 15:54:30 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "philo.h"

static int	_func_abort(const char *str1, const char *str2)
{
	if (str2 == NULL)
		ft_dprintf(STDERR_FILENO, "Error: %s\n", str1);
	else
		ft_dprintf(STDERR_FILENO, "Error: %s: %s\n", str1, str2);
	return (FAILURE);
}

static int	_philo_atoi(const char *str, int *num_p)
{
	*num_p = 0;
	while (true)
	{
		if (*str == '\0')
			break ;
		if (*str < '0' && '9' < *str)
			return (FAILURE);
		if (*num_p > INT_MAX / 10 || (*num_p == INT_MAX / 10 && *str >= '7'))
			return (*num_p = INT_MAX, SUCCESS);
		*num_p = *num_p * 10 + *str - '0';
		str++;
	}
	return (SUCCESS);
}

static int	_set_data(t_data *d, const int argc, const char **argv)
{
	if (_philo_atoi(argv[1], &d->num_of_philos) == FAILURE)
		return (FAILURE);
	if (_philo_atoi(argv[2], &d->time2die) == FAILURE)
		return (FAILURE);
	if (_philo_atoi(argv[3], &d->time2eat) == FAILURE)
		return (FAILURE);
	if (_philo_atoi(argv[4], &d->time2sleep) == FAILURE)
		return (FAILURE);
	if (argc == ARGC_MAX)
	{
		if (_philo_atoi(argv[5], &d->num_of_times2eat) == FAILURE)
			return (FAILURE);
	}
	else
		d->num_of_times2eat = 0;
	return (SUCCESS);
}
// num_of_times2eat is 0, that is meaning endless

int	check_data_time(int time, const char *str)
{
	if (time < TIME_VALUE_MIN)
		return (_func_abort(str, "too little"));
	else if (time > TIME_VALUE_MAX)
		return (_func_abort(str, "too much"));
	return (SUCCESS);
}

int	process_input(t_data *d, const int argc, const char **argv)
{
	if (argc < ARGC_MIN || ARGC_MAX < argc)
		return (_func_abort("Wrong number of arguments", NULL));
	if (_set_data(d, argc, argv) == FAILURE)
		return (_func_abort("Input contains non-numeric characters", NULL));
	if (d->num_of_philos > NUM_OF_PHILOS_MAX)
		return (_func_abort("num_of_philos", "too many"));
	if (d->num_of_philos < NUM_OF_PHILOS_MIN)
		return (_func_abort("num_of_philos", "too few"));
	if (argc == ARGC_MAX)
	{
		if (d->num_of_times2eat > NUM_OF_TIMES_TO_EAT_MAX)
			return (_func_abort("num_of_times_to_eat", "too many"));
		if (d->num_of_times2eat < NUM_OF_TIMES_TO_EAT_MIN)
			return (_func_abort("num_of_times_to_eat", "too few"));
	}
	if (check_data_time(d->time2die, "time_to_die") == FAILURE
		|| check_data_time(d->time2eat, "time_to_eat") == FAILURE
		|| check_data_time(d->time2sleep, "time_to_sleep") == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
