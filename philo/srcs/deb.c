/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:32:57 by retanaka          #+#    #+#             */
/*   Updated: 2024/11/28 09:04:50 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deb_ft_put_argv_fd(const int fd, const int argc, const char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		ft_put_fd(fd, argv[i]);
		i++;
		if (i < argc)
			ft_put_fd(fd, ", ");
	}
	ft_putendl_fd(fd, "");
}

void	deb_print_data(t_data data)
{
	printf("%d, ", data.num_of_philos);
	printf("%d, ", data.time_to_die);
	printf("%d, ", data.time_to_eat);
	printf("%d, ", data.time_to_sleep);
	printf("%d\n", data.num_of_times_each_philo_must_eat);
}
