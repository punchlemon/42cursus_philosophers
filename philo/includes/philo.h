/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:46:13 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/03 16:09:33 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft.h"

enum
{
	FIRST = 0,
	SECOND_AFTER,
};

enum
{
	ALIVE = 0,
	THINKING_DIE,
	SLEEPING_DIE,
	DEAD,
};

// structs
typedef struct s_data
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_times_each_philo_must_eat;
}	t_data;

typedef pthread_mutex_t	t_fork;
typedef struct timeval	t_timeval;
typedef suseconds_t		t_time;

typedef struct s_philo
{
	pthread_t	tid;
	int			i;
	int			born;
	int			die;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_data		d;
	suseconds_t	last_eat_time;
	t_time		time_to_eat;
	t_time		time_to_sleep;
	t_time		time_between_eat;
	t_time		odd_delay_time;
	t_time		delta_delay_time;
}	t_philo;

// functions
// deb
void	deb_ft_put_argv_fd(const int fd, const int argc, const char **argv);
void	deb_print_data(t_data d);

// destroy
void	destroy(int num_of_forks, t_philo *philos, t_fork *forks);

// init
// int		create_philos(int *ret, t_data d, t_philo **philos, t_fork *forks);
// int		create_forks(int *ret, int num_of_forks, t_fork **forks);
// void	init_data(t_data *d, int argc, const char **argv);
int		run(int *ret, t_data d, t_philo **philos, t_fork **forks);

// life
void	*philo_life(void *arg);

#endif
