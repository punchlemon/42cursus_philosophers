/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_with_timestamp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:28:50 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/02 19:38:20 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_utils(t_philo *p, const char *str, long *now_p)
{
	long	now;
	int		result;

	if (priority_mutex_lock(p, PRINT_ID) == FAILURE)
		return (func_abort("Can't lock PRINT_ID", NULL));
	now = get_time();
	if (p->dead_time < now)
	{
		p->resources[DIED_ID].value = p->id;
		printf("%ld %ld %s\n", now - p->start_time, p->id, "died");
		result = FAILURE;
	}
	else
	{
		printf("%ld %ld %s\n", now - p->start_time, p->id, str);
		result = SUCCESS;
	}
	priority_mutex_unlock(p, PRINT_ID);
	if (now_p)
		*now_p = now;
	return (result);
}

int	print_with_timestamp(t_philo *p, const char *str, long *now_p)
{
	int	result;

	if (priority_mutex_lock(p, DIED_ID) == FAILURE)
		return (func_abort("Can't lock DIED_ID", NULL));
	if (p->resources[DIED_ID].value == FAILURE)
		result = print_utils(p, str, now_p);
	else
		result = FAILURE;
	priority_mutex_unlock(p, DIED_ID);
	return (result);
}
