/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:51 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/09 19:29:17 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_dprintf.h"

static void	_set_philo_time2think(t_philo *p)
{
	float	delta_time;

	if (p->id % 2)
		p->first_time2think = 0;
	else
		p->first_time2think = p->d.time2eat;
	delta_time = (float)p->d.time2eat / (float)(p->d.num_of_philos / 2);
	p->time2think = p->d.time2eat - p->d.time2sleep;
	if (p->d.num_of_philos != 1 && p->d.num_of_philos % 2)
	{
		p->first_time2think += (int)(delta_time * (p->id / 2));
		p->time2think += (int)delta_time;
	}
	if (p->time2think < 0)
		p->time2think = 0;
}

static void	_set_philo_fork(t_philo *p, pthread_mutex_t *forks)
{
	int		fork1_id;
	int		fork2_id;
	int		tmp;

	if (p->d.num_of_philos == 1)
	{
		p->fork1 = &forks[0];
		p->fork2 = NULL;
	}
	else
	{
		fork1_id = p->id - 1;
		fork2_id = (p->id % p->d.num_of_philos);
		if (fork1_id > fork2_id)
		{
			tmp = fork1_id;
			fork1_id = fork2_id;
			fork2_id = tmp;
		}
		p->fork1 = &forks[fork1_id];
		p->fork2 = &forks[fork2_id];
	}
}

static void	_set_philos(t_philo *philos, pthread_mutex_t *forks, t_super *super,
t_data d)
{
	long		i;
	t_philo		*philo;

	i = 0;
	while (i < d.num_of_philos)
	{
		philo = &philos[i];
		philo->super = super;
		philo->id = i + 1;
		philo->d = d;
		philo->start_time = 0;
		philo->dead_time = 0;
		philo->count = 0;
		philo->is_incompleted = (philo->d.num_of_times2eat != 0);
		_set_philo_time2think(&philos[i]);
		_set_philo_fork(&philos[i], forks);
		i++;
	}
}

static int	_create_philos(t_philo *philos, pthread_t *tids, int num_of_philos)
{
	long		i;

	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_create(&tids[i], NULL, simulate_philo, &philos[i]) != 0)
			break ;
		i++;
	}
	if (i == num_of_philos)
	{
		i = 0;
		while (i < num_of_philos)
			pthread_join(tids[i++], NULL);
		return (SUCCESS);
	}
	pthread_mutex_lock(&philos[i].super->mutex);
	philos[i].super->is_dead = true;
	pthread_mutex_unlock(&philos[i].super->mutex);
	while (i--)
		pthread_detach(tids[i]);
	ft_dprintf(STDERR_FILENO, "Error: philos creation failed\n");
	return (FAILURE);
}

int	start_simulation(t_philo *philos, pthread_mutex_t *forks, t_super *super,
t_data d)
{
	pthread_t	tids[NUM_OF_PHILOS_MAX];

	_set_philos(philos, forks, super, d);
	if (_create_philos(philos, tids, d.num_of_philos) == FAILURE)
		return (FAILURE);
	destroy_mutexes(forks, d.num_of_philos, super);
	return (SUCCESS);
}
