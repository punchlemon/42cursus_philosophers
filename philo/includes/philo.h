/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:46:13 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/09 17:58:12 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define ARGC_MIN 5
# define ARGC_MAX 6
# define TIME_VALUE_MIN 10
# define TIME_VALUE_MAX 100000
# define NUM_OF_PHILOS_MIN 1
# define NUM_OF_PHILOS_MAX 200
# define NUM_OF_FORKS_MAX 200
# define NUM_OF_TIMES_TO_EAT_MIN 1
# define NUM_OF_TIMES_TO_EAT_MAX 100000

# define KILO 1000
# define NYQUIST_INTERVAL 500

enum
{
	FAILURE = 0,
	SUCCESS,
};

enum
{
	FORK_ID = 1,
	SUPER_ID = FORK_ID + NUM_OF_FORKS_MAX,
	RESOURCES_LEN
};

typedef struct s_super
{
	pthread_mutex_t	mutex;
	long			start_time;
	int				completed_philos_num;
	bool			is_dead;
}	t_super;

typedef struct s_data
{
	int	num_of_philos;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int	num_of_times2eat;
}	t_data;
// when endless setting, you should is 0

typedef struct s_philo
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	t_super			*super;
	long			id;
	t_data			d;
	long			start_time;
	long			last_log_time;
	long			dead_time;
	int				count;
	int				is_incompleted;
	long			first_time2think;
	long			time2think;
}	t_philo;

int		start_simulation(t_philo *philos, pthread_mutex_t *forks,
			t_super *super, t_data d);
void	*simulate_philo(void *arg);

long	get_time(void);
long	philo_get_time(t_philo *p);

int		print_with_timestamp(t_philo *p, const char *str, long *now_p);

void	destroy_mutexes(pthread_mutex_t *forks, int i, t_super *super);

void	set_died(t_philo *p, int is_print);
int		my_msleep(long msec, t_philo *p);
int		process_input(t_data *d, const int argc, const char **argv);

#endif
