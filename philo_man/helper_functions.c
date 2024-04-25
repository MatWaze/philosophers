/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:19:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/25 15:55:08 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_epoch(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	init_obj(t_obj *obj, int argc, char **argv)
{
	int	i;

	if (argc == 6)
		obj->eat_count = ft_atoi(argv[5]);
	else
		obj->eat_count = -1;
	obj->philo_count = ft_atoi(argv[1]);
	obj->time_to_die = ft_atoi(argv[2]);
	obj->time_to_eat = ft_atoi(argv[3]);
	obj->time_to_sleep = ft_atoi(argv[4]);
	exit_cond(obj->time_to_die, obj->time_to_eat, obj->time_to_sleep, \
	obj->philo_count);
	obj->dead = 0;
	pthread_mutex_init(&obj->print_mutex, NULL);
	pthread_mutex_init(&obj->die, NULL);
	obj->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) \
	* obj->philo_count);
	i = 0;
	while (i < obj->philo_count)
		pthread_mutex_init(&obj->forks[i++], NULL);
}

void	init_philo(t_philo *philos, t_obj *obj)
{
	int	i;

	i = 0;
	while (i < obj->philo_count)
	{
		philos[i].count_ate = 0;
		philos[i].number = i;
		philos[i].obj = obj;
		philos[i].last_time_eat = get_epoch();
		pthread_mutex_init(&philos[i].last_time_eat_m, NULL);
		pthread_mutex_init(&philos[i].count_ate_m, NULL);
		i++;
	}
}

void	create_threads(t_obj *obj, t_philo *philos, \
	pthread_t *threads, void *(*philosophers) (void *))
{
	int	i;

	i = 0;
	while (i < obj->philo_count)
	{
		pthread_create(&threads[i], NULL, philosophers, &philos[i]);
		i++;
	}
}

void	join_threads(t_obj *obj, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < obj->philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
