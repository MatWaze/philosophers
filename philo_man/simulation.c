/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:51:19 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/25 17:30:22 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_finished_eating(t_philo *philos, t_obj *obj)
{
	int	i;
	int	ans;

	i = 0;
	ans = 0;
	while (i < obj->philo_count)
	{
		pthread_mutex_lock(&philos[i].count_ate_m);
		if (philos[i].count_ate >= obj->eat_count)
			ans++;
		pthread_mutex_unlock(&philos[i].count_ate_m);
		i++;
	}
	if (ans == obj->philo_count && obj->eat_count != -1)
	{
		pthread_mutex_lock(&obj->die);
		obj->dead = 1;
		pthread_mutex_unlock(&obj->die);
		return (1);
	}
	return (0);
}

int	philo_died(t_philo *philos, t_obj *obj)
{
	int	i;

	i = 0;
	while (i < philos->obj->philo_count)
	{
		pthread_mutex_lock(&philos[i].last_time_eat_m);
		pthread_mutex_lock(&obj->die);
		if (get_epoch() - philos[i].last_time_eat >= obj->time_to_die)
		{
			pthread_mutex_unlock(&obj->die);
			obj->dead = 1;
			pthread_mutex_unlock(&philos[i].last_time_eat_m);
			mutex_print(philos[i], "died");
			return (1);
		}
		pthread_mutex_unlock(&obj->die);
		pthread_mutex_unlock(&philos[i].last_time_eat_m);
		i++;
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	if (stop_simulation(philo->obj) == 1)
		return ;
	mutex_print(*philo, "is eating");
	philo_usleep(philo->obj->time_to_eat);
	pthread_mutex_lock(&philo->last_time_eat_m);
	philo->last_time_eat = get_epoch();
	pthread_mutex_unlock(&philo->last_time_eat_m);
	pthread_mutex_lock(&philo->count_ate_m);
	philo->count_ate++;
	pthread_mutex_unlock(&philo->count_ate_m);
}

void	philo_sleep(t_philo *philo)
{
	if (stop_simulation(philo->obj) == 1)
		return ;
	mutex_print(*philo, "is sleeping");
	philo_usleep(philo->obj->time_to_sleep);
}

void	*philosophers(void *data)
{
	t_philo			*philo;

	philo = (t_philo *) data;
	set_lr(philo);
	set_epoch(philo);
	if ((philo->number + 1) % 2 == 0)
		philo_usleep(philo->obj->time_to_eat);
	while (stop_simulation(philo->obj) == 0)
	{
		mutex_print(*philo, "is thinking");
		pthread_mutex_lock(&philo->l);
		mutex_print(*philo, "has taken a fork");
		if (philo->obj->philo_count == 1)
		{
			pthread_mutex_unlock(&philo->l);
			break ;
		}
		pthread_mutex_lock(&philo->r);
		mutex_print(*philo, "has taken a fork");
		philo_eat(philo);
		pthread_mutex_unlock(&philo->l);
		pthread_mutex_unlock(&philo->r);
		philo_sleep(philo);
	}
	return (NULL);
}
