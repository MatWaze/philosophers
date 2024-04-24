/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:19:26 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/23 17:34:45 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_obj
{
	pthread_t	*th;
	sem_t		*forks;
	sem_t		*print_sem;
	sem_t		*die_sem;
	sem_t		*last_time_eat_s;
	sem_t		*count_ate_s;
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_count;
	int			dead;
}		t_obj;

typedef struct s_philo
{
	long long		last_time_eat;
	int				number;
	int				count_ate;
	t_obj			*obj;

}		t_philo;

void		my_print(t_philo *philo, char *text);
void		init_obj(t_obj *obj, int argc, char **argv);
void		init_philo(t_philo *philos, t_obj *obj);
void		philo_usleep(int sleep_time);
void		kill_all(t_philo *philos, int *pid);
void		parent_process(t_philo *philos, int *pid);
void		children(t_philo *philos, pthread_t *threads, int *pid);
void		*philosophers(void *data);
int			philo_died(void *data);
int			ft_atoi(char *str);
long long	get_epoch(void);

#endif