/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:58:42 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/05 15:39:15 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork(t_philo *p)
{
	while (1)
	{
		if (pthread_mutex_lock(p->left_fork) == 0)
		{
			if (check_print_time(p, "has taken a fork") == -1)
				return ;
			if (pthread_mutex_lock(p->right_fork) == 0)
			{
				if (check_print_time(p, "has taken a fork") == -1)
					return ;
				break ;
			}
			pthread_mutex_unlock(p->left_fork);
		}
	}
}

int	philo_eat(t_philo *p)
{
	get_fork(p);
	if (check_print_time(p, "is eating") != END)
		usleep(p->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (p->die);
}
