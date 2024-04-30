/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:19:26 by mamazari          #+#    #+#             */
/*   Updated: 2024/04/30 11:32:23 by mamazari         ###   ########.fr       */
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

typedef struct s_obj
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	die;
	pthread_mutex_t	*forks;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				dead;
}		t_obj;

typedef struct s_philo
{
	pthread_mutex_t	last_time_eat_m;
	pthread_mutex_t	count_ate_m;
	pthread_mutex_t	*l;
	pthread_mutex_t	*r;
	long long		last_time_eat;
	int				number;
	int				count_ate;
	t_obj			*obj;

}		t_philo;

void		mutex_print(t_philo philo, char *text);
void		set_lr(t_philo *philo);
void		set_epoch(t_philo *philo);
void		exit_cond(int ttd, int tte, int tts, int pc);
void		init_obj(t_obj *obj, int argc, char **argv);
void		init_philo(t_philo *philos, t_obj *obj);
void		philo_usleep(int sleep_time);
void		*philosophers(void *data);
void		destroy_mutexes(t_philo *philos);
void		free_all(t_philo *philos, pthread_t *threads);
void		create_threads(t_obj *obj, t_philo *philos, \
	pthread_t *threads, void *(*philosophers) (void *));
void		join_threads(t_obj *obj, pthread_t *threads);
int			stop(t_philo *philo);
int			stop_simulation(t_obj *obj);
int			all_finished_eating(t_philo *philos, t_obj *obj);
int			philo_died(t_philo *philos, t_obj *obj);
int			ft_atoi(char *str);
int			error_msg(void);
long long	get_epoch(void);

#endif