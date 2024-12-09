/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:51 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/09 23:31:26 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)arg;
	i = 0;
	while (1)
	{
		if (philo_think(p) == FAILURE)
			return ((void *)p);
		if (philo_eat(p, i) == FAILURE)
			return ((void *)p);
		if (philo_sleep(p) == FAILURE)
			return ((void *)p);
		i++;
	}
	return ((void *)p);
}
