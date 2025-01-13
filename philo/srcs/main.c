/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:06 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/14 02:16:02 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	numeric_args(const int argc, const char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (FAILURE);
			j++;
		}
		if (j == 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	zerofilling_args(const int argc, const char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '0' && argv[i][1])
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	set_pvals(t_pval *pvals)
{
	int	i;

	i = 0;
	while (i < PVALS_LEN)
	{
		if (pthread_mutex_init(&pvals[i].mutex, NULL) != 0)
			break ;
		pvals[i].value = FAILURE;
		i++;
	}
	if (i == PVALS_LEN)
		return (SUCCESS);
	while (i)
		pthread_mutex_destroy(&pvals[--i].mutex);
	return (FAILURE);
}

void	wait_philos(int num_of_philos, t_philo *philos)
{
	long	i;
	void	*ret;
	long	died_id;

	died_id = -1;
	i = 0;
	while (i < num_of_philos)
	{
		pthread_join(philos[i].tid, &ret);
		if (philos[i].is_dead)
			died_id = i;
		i++;
	}
	if (died_id != -1)
		printf("%ld %ld died\n", get_time(), died_id + 1);
}

int	main(const int argc, const char **argv)
{
	t_data	d;
	t_philo	*philos;
	t_fork	*forks;
	t_pval	pvals[PVALS_LEN];

	if (argc < ARGC_MIN || argc > ARGC_MAX)
		return (proc_abort("Wrong number of arguments"));
	if (numeric_args(argc, argv) == FAILURE)
		return (proc_abort("Non-numeric arguments"));
	if (zerofilling_args(argc, argv) == FAILURE)
		return (proc_abort("Zerofilling number are not accepted"));
	if (set_pvals(pvals) == FAILURE)
		return (proc_abort("Mutex creation failure"));
	if (set_and_check_data(&d, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (create_forks(d.num_of_philos, &forks) == FAILURE)
		return (destroy(d.num_of_philos, NULL, NULL, pvals), EXIT_FAILURE);
	if (create_philos(d, &philos, forks, pvals) == FAILURE)
		return (destroy(d.num_of_philos, NULL, forks, pvals), EXIT_FAILURE);
	wait_philos(d.num_of_philos, philos);
	destroy(d.num_of_philos, philos, forks, pvals);
	return (EXIT_SUCCESS);
}
