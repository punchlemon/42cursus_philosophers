/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:00:40 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/05 15:01:10 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_other_die(t_philo *p)
{
	while (pthread_mutex_lock(&(p->flags->checkable)))
		;
	if (p->flags->died == DEAD)
		p->die = END;
	pthread_mutex_unlock(&(p->flags->checkable));
	return (p->die);
}

void	philo_die(t_philo *p)
{
	while (pthread_mutex_lock(&(p->flags->checkable)))
		;
	if (p->flags->died != DEAD)
	{
		p->flags->died = DEAD;
		print_time(p, "died");
		p->die = DEAD;
	}
	else
		p->die = END;
	pthread_mutex_unlock(&(p->flags->checkable));
}
