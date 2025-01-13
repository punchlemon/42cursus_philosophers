/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:46:13 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/11 13:25:02retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ARGC_MIN 5
# define ARGC_MAX 6
# define TIME_VALUE_MIN 10
# define TIME_VALUE_MAX 1000000
# define NUM_OF_PHILO_MIN 1
# define NUM_OF_PHILO_MAX 200
# define KILO 1000

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

enum
{
	FAILURE = 0,
	SUCCESS,
};

enum
{
	THREAD_READY = 0,
	THREAD_RUNNING,
	THREAD_HALTED,
};

enum
{
	PRINT_ID = 0,
	START_ID,
	STATUS_ID,
	PVALS_LEN,
};

typedef pthread_t t_tid;
typedef pthread_mutex_t	t_mutex;

typedef struct s_pval
{
	t_mutex	mutex;
	long	value;
}	t_pval;

typedef t_pval t_fork;

typedef struct s_data
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_think;
	int	num_of_times_to_eat;
	int	argc;
}	t_data;

typedef struct s_philo
{
	t_tid	tid;
	long	id;
	t_data	d;

	t_pval	*pvals;
	t_fork	*left_fork;
	t_fork	*right_fork;
	long	dead_time;
	long	time_to_first_think;
	bool	is_dead;
}	t_philo;

int		func_abort(const char *str1, const char *str2);
int		proc_abort(const char *str);
int		create_forks(int num_of_forks, t_fork **forks);
int		create_philos(t_data d, t_philo **ps_p, t_fork *forks, t_pval *pvals);
void	destroy(int num_of_frks, t_philo *philos, t_fork *forks, t_pval *pvals);
int		ft_atoi(const char *str);
void	*philo_life(void *arg);
long	get_time(void);
long	print_with_timestamp_safe(t_philo *p, const char *str);
void	set_mutex_value(t_pval *pval, long value);
long	get_mutex_value(t_pval *pval);
void	destroy_mutexes(int num_of_pvals, t_pval *pvals);
int		my_sleep(long goal, t_philo *p);
int		philo_eat(t_philo *p);
int		set_and_check_data(t_data *d, int argc, const char **argv);

#endif
