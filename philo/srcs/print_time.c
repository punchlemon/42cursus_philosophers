/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:58:02 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/05 14:58:17 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	get_time(void)
{
	t_timeval	tv;
	t_time		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	print_time(t_philo *p, const char *src)
{
	t_time	now;

	while (pthread_mutex_lock(&(p->flags->printable)))
		;
	now = get_time();
	if (src)
		printf("%ld %d %s\n", now, p->i, src);
	pthread_mutex_unlock(&(p->flags->printable));
	return ;
}

int	check_print_time(t_philo *p, const char *src)
{
	while (pthread_mutex_lock(&(p->flags->checkable)))
		;
	if (p->flags->died == DEAD)
	{
		pthread_mutex_unlock(&(p->flags->checkable));
		p->die = END;
	}
	else
		print_time(p, src);
	pthread_mutex_unlock(&(p->flags->checkable));
	return (p->die);
}
