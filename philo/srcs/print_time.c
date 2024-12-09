/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:58:02 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/09 18:07:13 by retanaka         ###   ########.fr       */
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
	printf("%ld %d %s\n", now, p->i + 1, src);
	pthread_mutex_unlock(&(p->flags->printable));
}

t_time	check_print_time(t_philo *p, const char *src)
{
	t_time	now;

	now = get_time();
	{
		pthread_mutex_lock(&(p->flags->checkable));
		if (now >= p->dead_time)
		{
			if (p->flags->died == END)
				p->die = END;
			else
			{
				print_time(p, "died", now);
				p->die = DEAD;
				p->flags->died = END;
			}
		}
		if (p->flags->died == END)
			p->die = END;
		else
			print_time(p, src, now);
		pthread_mutex_unlock(&(p->flags->checkable));
		if (p->die != ALIVE)
			return (FAILURE);
	}
	return (now);
}
