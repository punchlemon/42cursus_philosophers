/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:46:13 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/06 13:44:27 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

enum
{
	FIRST = 0,
	SECOND_AFTER,
};

enum
{
	ALIVE = 0,
	THINKING_DIE,
	EATING_DIE,
	SLEEPING_DIE,
	DEAD,
	END,
};

// typedefs
typedef pthread_mutex_t	t_fork;
typedef pthread_mutex_t	t_flag;
typedef struct timeval	t_timeval;
// typedef suseconds_t		t_time;
typedef long			t_time;

typedef struct s_flags
{
	t_flag	printable;
	t_flag	checkable;
	int		died;
}	t_flags;

typedef struct s_data
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_times_each_philo_must_eat;
}	t_data;

typedef struct s_philo
{
	pthread_t	tid;
	int			i;
	int			born;
	int			die;
	t_flags		*flags;
	t_fork		*left_fork;
	t_fork		*right_fork;
	suseconds_t	last_eat_time;
	int			num_of_philos;
	t_time		time_to_die;
	t_time		time_to_eat;
	t_time		time_to_sleep;
	t_time		time_to_first_think;
	t_time		time_to_second_after_think;
	int			num_of_times_each_philo_must_eat;
}	t_philo;

// functions
// eat
int		philo_eat(t_philo *p);

// ft_atoi
int		ft_atoi(const char *str);

// sleep
int		philo_sleep(t_philo *p);

// think
void	philo_think(t_philo *p);

// print_time
t_time	get_time(void);
void	print_time(t_philo *p, const char *src);
int		check_print_time(t_philo *p, const char *src);

// die
int		check_other_die(t_philo *p);
void	philo_die(t_philo *p);

// destroy
void	destroy(int num_of_forks, t_philo *philos, t_fork *forks);

// init
// int		create_philos(int *ret, t_data d, t_philo **philos, t_fork *forks);
// int		create_forks(int *ret, int num_of_forks, t_fork **forks);
// void	init_data(t_data *d, int argc, const char **argv);
int		run(t_data d, t_philo **philos, t_fork **forks);

// life
void	*philo_life(void *arg);

#endif
