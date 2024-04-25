/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:53:42 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/25 17:32:38 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_print(t_philo philo, char *text)
{
	pthread_mutex_lock(&philo.obj->print_mutex);
	printf("%lld %d %s\n", get_epoch(), philo.number + 1, text);
	pthread_mutex_unlock(&philo.obj->print_mutex);
}

int	stop_simulation(t_obj *obj)
{
	int	ans;

	ans = 0;
	pthread_mutex_lock(&obj->die);
	ans = obj->dead;
	pthread_mutex_unlock(&obj->die);
	return (ans);
}

void	philo_usleep(int sleep_time)
{
	long long	time;

	time = get_epoch();
	while ((get_epoch() - time) < sleep_time)
		usleep(500);
}

void	destroy_mutexes(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->obj->philo_count)
	{
		pthread_mutex_destroy(&philos[i].count_ate_m);
		pthread_mutex_destroy(&philos[i].last_time_eat_m);
		pthread_mutex_destroy(&philos->obj->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->obj->print_mutex);
	pthread_mutex_destroy(&philos->obj->die);
}

void	free_all(t_philo *philos, pthread_t *threads)
{
	free(threads);
	free(philos->obj->forks);
	free(philos);
}
