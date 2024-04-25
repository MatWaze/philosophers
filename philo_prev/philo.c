/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:19:20 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/23 14:08:59 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(void)
{
	printf("Usage: philo_count time_to_die time_to_eat \
time_to_sleep [to_eat_count]\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_obj		obj;
	t_philo		*philos;
	pthread_t	*threads;

	if (argc > 4 && argc < 7)
	{
		init_obj(&obj, argc, argv);
		threads = (pthread_t *) malloc(sizeof(pthread_t) * obj.philo_count);
		philos = (t_philo *) malloc(sizeof(t_philo) * obj.philo_count);
		init_philo(philos, &obj);
		create_threads(&obj, philos, threads, philosophers);
		while (1)
		{
			if (philo_died(philos, &obj) == 1 || \
			all_finished_eating(philos, &obj) == 1)
				break ;
		}
		join_threads(&obj, threads);
		destroy_mutexes(philos);
		free_all(philos, threads);
	}
	else
		return (error_msg());
	return (0);
}
