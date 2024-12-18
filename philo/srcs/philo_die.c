/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:00:40 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/09 16:34:07 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_die(t_philo *p)
{
	int		die;
	t_time	now;

	pthread_mutex_lock(&(p->flags->checkable));
	die = p->flags->died;
	if (die != END)
	{
		now = get_time();
		p->flags->died = END;
		print_time(p, "died", now);
	}
	pthread_mutex_unlock(&(p->flags->checkable));
	if (die != END)
		p->die = DEAD;
	else
		p->die = END;
}
