/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:47:07 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/25 16:31:57 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_lr(t_philo *philo)
{
	philo->l = philo->obj->forks[philo->number];
	philo->r = philo->obj->forks[(philo->number + 1) % philo->obj->philo_count];
}

void	set_epoch(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_time_eat_m);
	philo->last_time_eat = get_epoch();
	pthread_mutex_unlock(&philo->last_time_eat_m);
}

long	ft_atoi(char *str)
{
	long	number;
	int		i;
	int		minus;

	number = 0;
	i = 0;
	minus = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			minus = -1;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			number = number * 10 + str[i] - '0';
		else
			exit(error_msg());
		i++;
	}
	if (number * minus <= 0)
		exit(error_msg());
	return (number * minus);
}
