/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:48:16 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/07 13:20:24 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_sleep(t_time goal, t_philo *p)
{
	t_time	now;

	now = get_time();
	while (now < goal)
	{
		now = get_time();
		if (now >= p->dead_time)
			return (philo_die(p), FAILURE);
	}
	return (SUCCESS);
}
