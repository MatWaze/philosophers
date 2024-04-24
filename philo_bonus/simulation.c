/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:51:19 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/23 17:12:13 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	my_print(philo, "is eating");
	philo_usleep(philo->obj->time_to_eat);
	sem_wait(philo->obj->count_ate_s);
	philo->count_ate++;
	sem_post(philo->obj->count_ate_s);
}

void	philo_sleep(t_philo *philo)
{
	my_print(philo, "is sleeping");
	philo_usleep(philo->obj->time_to_sleep);
}

void	last_eat_time(t_philo *philo)
{
	sem_wait(philo->obj->last_time_eat_s);
	struct timeval	t;

	gettimeofday(&t, NULL);
	philo->last_time_eat = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	sem_post(philo->obj->last_time_eat_s);
}

void	*philosophers(void *data)
{
	t_philo			*philo;

	philo = (t_philo *) data;
	if ((philo->number + 1) % 2 == 0)
		philo_usleep(philo->obj->time_to_eat);
	while (1)
	{
		sem_wait(philo->obj->forks);
		my_print(philo, "is thinking");
		my_print(philo, "has taken a fork");
		sem_wait(philo->obj->forks);
		my_print(philo, "has taken a fork");
		philo_eat(philo);
		sem_post(philo->obj->forks);
		sem_post(philo->obj->forks);
		last_eat_time(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
