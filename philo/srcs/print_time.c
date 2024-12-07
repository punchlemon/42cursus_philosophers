/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:58:02 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/07 13:17:57 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	get_time(void)
{
	t_timeval	tv;
	long		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * (long)1000 + tv.tv_usec / (long)1000;
	return (time);
}

void	print_time(t_philo *p, const char *src, t_time now)
{
	pthread_mutex_lock(&(p->flags->printable));
	printf("%ld %d %s\n", now, p->i, src);
	pthread_mutex_unlock(&(p->flags->printable));
}

t_time	check_print_time(t_philo *p, const char *src)
{
	t_time	now;

	now = get_time();
	if (now >= p->dead_time)
		return (philo_die(p), FAILURE);
	else if (src)
	{
		pthread_mutex_lock(&(p->flags->checkable));
		if (p->flags->died != END)
			print_time(p, src, now);
		pthread_mutex_unlock(&(p->flags->checkable));
	}
	return (now);
}
