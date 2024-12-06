/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:58:42 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/06 20:39:59 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (check_print_time(p, "has taken a fork") == -1)
		return ;
	pthread_mutex_lock(p->right_fork);
	if (check_print_time(p, "has taken a fork") == -1)
		return ;
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
