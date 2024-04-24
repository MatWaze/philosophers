/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:53:42 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/23 17:19:12 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_epoch(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	my_print(t_philo *philo, char *text)
{
	sem_wait(philo->obj->print_sem);
	printf("%lld %d %s\n", get_epoch(), philo->number + 1, text);
	sem_post(philo->obj->print_sem);
}

void	kill_all(t_philo *philos, int *pid)
{
	int	i;

	i = 0;
	while (i < philos->obj->philo_count)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
}

void	philo_usleep(int sleep_time)
{
	long long	time;

	time = get_epoch();
	while ((get_epoch() - time) < sleep_time)
		usleep(500);
}
