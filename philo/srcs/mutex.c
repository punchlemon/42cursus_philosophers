/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 08:16:58 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/18 14:29:26 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * (long)KILO + tv.tv_usec / (long)KILO;
	return (time);
}
// get_time no check

long	print_with_timestamp_safe(t_philo *p, const char *str)
{
	long	now;

	now = 0;
	pthread_mutex_lock(&p->pvals[STATUS_ID].mutex);
	if (p->pvals[STATUS_ID].value != THREAD_HALTED)
	{
		pthread_mutex_lock(&p->pvals[PRINT_ID].mutex);
		now = get_time();
		if (p->dead_time < now)
		{
			now = FAILURE;
			p->pvals[STATUS_ID].value = THREAD_HALTED;
			p->is_dead = true;
		}
		else
			printf("%ld %ld %s\n", now, p->id, str);
		pthread_mutex_unlock(&p->pvals[PRINT_ID].mutex);
	}
	else
		now = FAILURE;
	pthread_mutex_unlock(&p->pvals[STATUS_ID].mutex);
	return (now);
}

void	set_mutex_value(t_pval *pval, long value)
{
	pthread_mutex_lock(&pval->mutex);
	pval->value = value;
	pthread_mutex_unlock(&pval->mutex);
}

long	get_mutex_value(t_pval *pval)
{
	long	value;

	pthread_mutex_lock(&pval->mutex);
	value = pval->value;
	pthread_mutex_unlock(&pval->mutex);
	return (value);
}

void	destroy_mutexes(int num_of_pvals, t_pval *pvals)
{
	int	i;

	i = 0;
	while (i < num_of_pvals)
	{
		pthread_mutex_destroy(&pvals[i].mutex);
		i++;
	}
}
