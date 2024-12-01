/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/01 12:53:01by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_timestamp(int philo_i, const char *src, t_time *time)
{
	int			ret;
	t_timeval	tv;
	t_time		msec;

	ret = gettimeofday(&tv, NULL);
	if (ret != 0)
		return (ft_putendl_fd(2, "gettimeofday failed"), ret);
	msec = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("%ld %d %s\n", msec, philo_i, src);
	if (time)
		*time = msec;
	return (ret);
}

int	philo_take_a_fork(t_philo *philo, t_fork *fork)
{
	int	ret;

	if (pthread_mutex_lock(fork) == 0)
	{
		ret = print_timestamp(philo->i, "has taken a fork", NULL);
		if (ret != 0)
			return (ERROR);
		return (GET_FORK);
	}
	return (1);
}

int	philo_think(t_philo *philo, int *born)
{
	if (*born)
	{
		*born = 1;
		usleep(philo->i * 10 * 1000);
	}
	print_timestamp(philo->i, "is thinking", NULL);
	philo->status = THINKING;
	if (philo_take_a_fork(philo, philo->left_fork) == GET_FORK
		&& philo_take_a_fork(philo, philo->right_fork) == GET_FORK)
		return (EATING);
	if (1) // if you can sleep
		return (SLEEPING);
}

int	philo_eat(t_philo *philo)
{
	print_timestamp(philo->i, "is eating", &(philo->last_eat_usec));
	philo->status = EATING;
	usleep(philo->data.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	print_timestamp(philo->i, "is sleeping", NULL);
	usleep(philo->data.time_to_sleep);
	return (0);
}

void	*philo_life(void *arg)
{
	void	*retval;
	t_philo	*philo;
	int		born;
	int		next_move;

	(void)retval;
	philo = (t_philo *)arg;
	born = 0;
	while (1)
	{
		next_move = philo_think(philo, &born);
		if (next_move == EATING)
			philo_eat(philo);
		else if (next_move == SLEEPING)
			philo_sleep(philo);
		else if (next_move == DIED)
			return ((void *)NULL);
		else if (next_move == ERROR)
			return ((void *)NULL);// Wanna tell Error
	}
	return ((void *)0); // Cannt reachable
}
