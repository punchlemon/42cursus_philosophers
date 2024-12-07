/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:02:13 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/07 13:18:54 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *p)
{
	t_time	now;
	int		ret;

	now = check_print_time(p, "is sleeping");
	if (now == FAILURE)
		return (FAILURE);
	ret = my_sleep(p->last_move_time + p->time_to_sleep, p);
	p->last_move_time = now;
	return (ret);
}
