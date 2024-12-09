/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:58:42 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/07 13:14:54y retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork(t_philo *p)
{
	if (!p->right_fork)
		return (FAILURE);
	pthread_mutex_lock(p->left_fork);
	if (check_print_time(p, "has taken a fork") == FAILURE)
		return (pthread_mutex_unlock(p->left_fork), FAILURE);
	pthread_mutex_lock(p->right_fork);
	if (check_print_time(p, "has taken a fork") == FAILURE)
		return (pthread_mutex_unlock(p->left_fork)
			, pthread_mutex_unlock(p->right_fork), FAILURE);
	return (SUCCESS);
}

int	philo_eat(t_philo *p)
{
	int		ret;

	ret = FAILURE;
	if (get_fork(p) == FAILURE)
		return (FAILURE);
	p->last_move_time = check_print_time(p, "is eating");
	if (p->last_move_time == FAILURE)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		return (FAILURE);
	}
	p->dead_time = p->last_move_time + p->time_to_die;
	ret = my_sleep(p->last_move_time + p->time_to_eat, p);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (ret);
}
