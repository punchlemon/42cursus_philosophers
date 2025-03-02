/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:46:13 by retanaka          #+#    #+#             */
/*   Updated: 2025/03/02 19:10:30 by retanaka         ###   ########.fr       */
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
	START_ID = FORK_ID + NUM_OF_FORKS_MAX,
	COMPLETED_ID,
	DIED_ID,
	PRINT_ID,
	RESOURCES_LEN
};

typedef struct s_resource
{
	pthread_mutex_t	mutex;
	long			value;
}	t_resource;

typedef struct s_data
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_times_to_eat;
}	t_data;
// when endless setting, you should is 0

typedef struct s_philo
{
	long		id;
	t_data		d;
	t_resource	*resources;
	long		dead_time;
	long		first_time_to_think;
	int			locked_resources[RESOURCES_LEN];
	int			count;
	int			is_incompleted;
}	t_philo;

int		func_abort(const char *str1, const char *str2);
int		create_philos(t_data d, pthread_t *tids, t_philo *philos,
			t_resource *resources);
void	*start_philo_life(void *arg);

long	get_time(void);
int		print_with_timestamp(t_philo *p, const char *str, long *now_p);

int		set_mutex_value(t_philo *p, int id, long value);
int		get_mutex_value(t_philo *p, int id, long *value_p);
int		priority_mutex_lock(t_philo *p, int id);
void	priority_mutex_unlock(t_philo *p, int id);
void	destroy_mutexes(t_resource *resources, int i);

void	set_died(t_philo *p);
int		my_msleep(long start, long msec, t_philo *p);
int		process_input(t_data *d, const int argc, const char **argv);

int		philo_eat(t_philo *p);

#endif
