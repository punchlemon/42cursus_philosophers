/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:03:47 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/05 15:04:15 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_first_think(t_philo *p)
{
	p->time_to_think = 0;
	p->born = SECOND_AFTER;
	if (p->i % 2)
		p->time_to_think += p->time_to_eat;
	if (p->num_of_philos % 2)
		p->time_to_think += ((p->i + 1) / 2) * p->delta_delay_time;
	if (p->time_to_think > p->time_to_die)
	{
		p->die = THINKING_DIE;
		p->time_to_think = p->time_to_die;
	}
	else if (p->time_to_sleep > p->time_to_die)
	{
		p->die = SLEEPING_DIE;
		p->time_to_sleep = p->time_to_die;
	}
}

void	philo_second_after_think(t_philo *p)
{
	p->time_to_think = p->time_to_eat - p->time_to_sleep + p->delta_delay_time;
}

void	philo_think(t_philo *p)
{
	if (check_print_time(p, "is thinking") == END)
		return ;
	if (p->born == FIRST)
		philo_first_think(p);
	else
		philo_second_after_think(p);
	usleep(p->time_to_think);
	if (p->die == THINKING_DIE)
		return (philo_die(p));
	if (philo_eat(p) == END)
		return ;
	if (philo_sleep(p) == END)
		return ;
	if (p->die == SLEEPING_DIE)
		return (philo_die(p));
}
