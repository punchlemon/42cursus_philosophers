/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:03:47 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/06 13:00:55 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *p)
{
	if (check_print_time(p, "is thinking") == END)
		return ;
	if (p->born == FIRST)
	{
		p->born = SECOND_AFTER;
		usleep(p->time_to_first_think);
	}
	else
		usleep(p->time_to_second_after_think);
	if (p->die == THINKING_DIE)
		return (philo_die(p));
	if (philo_eat(p) == END)
		return ;
	if (philo_sleep(p) == END)
		return ;
	if (p->die == SLEEPING_DIE)
		return (philo_die(p));
}
