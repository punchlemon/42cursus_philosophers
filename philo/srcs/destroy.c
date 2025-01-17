/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:01:22 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/13 12:30:23 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(int num_of_frks, t_philo *philos, t_fork *forks, t_pval *pvals)
{
	destroy_mutexes(PVALS_LEN, pvals);
	free(philos);
	if (forks != NULL)
	{
		destroy_mutexes(num_of_frks, forks);
		free(forks);
	}
}
