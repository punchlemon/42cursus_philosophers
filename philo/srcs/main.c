/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:06 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/09 18:10:59 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_dprintf.h"

long	philo_get_time(t_philo *p)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * (long)KILO + tv.tv_usec / (long)KILO;
	return (time - p->start_time);
}
// get_time no check

void	destroy_mutexes(pthread_mutex_t *forks, int i, t_super *super)
{
	if (super)
		pthread_mutex_destroy(&super->mutex);
	while (i)
		pthread_mutex_destroy(&forks[--i]);
}

static int	_set_resources(pthread_mutex_t *forks, t_super *super_p, int num_of_forks)
{
	int	i;

	i = 0;
	while (true)
	{
		if (pthread_mutex_init(&forks[i++], NULL) != 0)
			break ;
		if (i == num_of_forks)
		{
			if (pthread_mutex_init(&super_p->mutex, NULL) != 0)
				break ;
			super_p->start_time = 0;
			super_p->completed_philos_num = 0;
			super_p->is_dead = false;
			return (SUCCESS);
		}
	}
	ft_dprintf(STDERR_FILENO, "Error: mutex creation failure\n");
	destroy_mutexes(forks, i, NULL);
	return (FAILURE);
}

int	print_with_timestamp(t_philo *p, const char *str, long *now_p)
{
	long	now;
	int		result;

	result = FAILURE;
	pthread_mutex_lock(&p->super->mutex);
	if (!p->super->is_dead)
	{
		now = philo_get_time(p);
		if (now_p)
			*now_p = now;
		if (now < p->dead_time)
		{
			result = SUCCESS;
			printf("%ld %ld %s\n", now, p->id, str);
		}
		else
		{
			p->super->is_dead = true;
			printf("%ld %ld %s\n", now, p->id, "died");
		}
	}
	pthread_mutex_unlock(&p->super->mutex);
	return (result);
}

int	main(const int argc, const char **argv)
{
	t_data			d;
	t_super			super;
	pthread_mutex_t	forks[NUM_OF_FORKS_MAX];
	t_philo			philos[NUM_OF_PHILOS_MAX];

	if (process_input(&d, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (_set_resources(forks, &super, d.num_of_philos) == FAILURE)
		return (EXIT_FAILURE);
	if (start_simulation(philos, forks, &super, d) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
