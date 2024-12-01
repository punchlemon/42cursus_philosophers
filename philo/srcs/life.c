/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/01 16:27:33 by retanaka         ###   ########.fr       */
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
	(void)fork;/// forkを取れてるかどうかを確かめる
	print_timestamp(philo->i, "has taken a fork", NULL);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	print_timestamp(philo->i, "is eating", &(philo->last_eat_usec));
	philo->status = EATING;
	usleep(philo->data.time_to_eat * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (philo->status != THINKING)
	{
		print_timestamp(philo->i, "is thinking", NULL);
		philo->status = THINKING;
	}
	// forkが取れるかどうかを模索中
	philo_take_a_fork(philo, philo->left_fork);
	philo_take_a_fork(philo, philo->right_fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	print_timestamp(philo->i, "is sleeping", NULL);
	usleep(philo->data.time_to_sleep * 1000);
	return (0);
}

void	*philo_life(void *arg)
{
	int		ret;
	void	*retval;
	t_philo	*philo;

	(void)retval;
	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->i % 2)// 奇数の人は食べても問題ない    哲学者の総数が奇数の場合にはかなり実装が異なる
			ret = philo_eat(philo);
		else
			philo_think(philo);
		philo_sleep(philo);
		if (ret != 0)
			return ((void *)NULL);// (void *)retだとエラーが出た
	}
	return ((void *)0);
}
