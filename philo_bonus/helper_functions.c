/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:19:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/23 17:38:23 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->obj->philo_count)
	{
		sem_wait(philo->obj->die_sem);
		if (get_epoch() - philo[i].last_time_eat > philo->obj->time_to_die)
		{
			my_print(&philo[i], "died");
			sem_post(philo->obj->die_sem);
			return (1);
		}
		sem_post(philo->obj->die_sem);
		i++;
	}
	return (0);
}

int	philo_ate(t_philo *philo)
{
	int	i;
	int	ans;

	i = 0;
	ans = 0;
	while (i < philo->obj->philo_count)
	{
		sem_wait(philo->obj->count_ate_s);
		if (philo[i].count_ate >= philo->obj->eat_count)
			ans++;
		sem_post(philo->obj->count_ate_s);
		i++;
	}
	return (ans == philo->obj->philo_count);
}

void	*stop_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	while (1)
	{
		if (philo_died(philo) == 1 || philo_ate(philo) == 1)
			break ;
	}
	pthread_join(philo->obj->th, NULL);
	return (NULL);
}


void	parent_process(t_philo *philos, int *pid)
{
	int	status;
	int	i;

	i = 0;
	while (i < philos->obj->philo_count)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
			kill_all(philos, pid);
		i++;
	}
}

void	children(t_philo *philos, pthread_t *threads, int *pid)
{
	int	i;

	i = 0;
	while (i < philos->obj->philo_count)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			pthread_create(&threads[i], NULL, stop_simulation, &philos[i]);
			philosophers(&philos[i]);
		}
		i++;
	}
}
