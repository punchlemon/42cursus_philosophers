/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/03 13:59:38by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	void	*retval;
	t_philo	*p;

	(void)retval;
	p = (t_philo *)arg;
	while (1)
	{
		philo_think(p);
		if (p->die == DEAD || p->die == END)
			return ((void *)0);
	}
	return ((void *)0); // Cant reachable
}