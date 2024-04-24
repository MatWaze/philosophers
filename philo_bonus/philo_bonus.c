/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:19:20 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/23 17:35:23 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlink_sems(void)
{
	sem_unlink("/forks");
	sem_unlink("/die");
	sem_unlink("/print");
	sem_unlink("/last_eat");
	sem_unlink("/count_ate");
}

void	init_obj(t_obj *obj, int argc, char **argv)
{
	if (argc == 6)
		obj->eat_count = ft_atoi(argv[5]);
	else
		obj->eat_count = INT_MAX;
	obj->philo_count = ft_atoi(argv[1]);
	obj->time_to_die = ft_atoi(argv[2]);
	obj->time_to_eat = ft_atoi(argv[3]);
	obj->time_to_sleep = ft_atoi(argv[4]);
	unlink_sems();
	obj->forks = sem_open("/forks", O_CREAT, 0777, obj->philo_count);
	obj->die_sem = sem_open("/die", O_CREAT, 0777, 1);
	obj->print_sem = sem_open("/print", O_CREAT, 0777, 1);
	obj->last_time_eat_s = sem_open("/last_eat", O_CREAT, 0777, 1);
	obj->count_ate_s = sem_open("/count_ate", O_CREAT, 0777, 1);
	obj->dead = 0;
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
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_obj		obj;
	t_philo		*philos;
	pthread_t	*threads;
	int			*pid;

	if (argc > 4 && argc < 7)
	{
		init_obj(&obj, argc, argv);
		philos = (t_philo *) malloc(sizeof(t_philo) * obj.philo_count);
		pid = (int *) malloc(sizeof(int) * obj.philo_count);
		threads = (pthread_t *) malloc(sizeof(pthread_t) * obj.philo_count);
		(&obj)->th = threads;
		init_philo(philos, &obj);
		children(philos, threads, pid);
		parent_process(philos, pid);
	}
	else
	{
		printf("Usage: philo_count time_to_die time_to_eat \
time_to_sleep [to_eat_count]\n");
		return (1);
	}
	return (0);
}
