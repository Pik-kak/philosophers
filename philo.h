/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:19:59 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/20 22:13:48 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

# define PHILOS_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				*philos_count;
	size_t			*time_to_die;
	size_t			*time_to_eat;
	size_t			*time_to_sleep;
	size_t			start;
	int				eating;
	size_t			last_ate;
	int				*meals;
	int				meals_count;
	int				*drink_poison;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}			t_philo;

typedef struct s_data
{
	int					philos_count;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					meals;
	int					drink_poison;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		meal_lock;
	t_philo				*philosophers;
}			t_data;

//utils.c
int		check_args(char **args);
int		ft_atoi(const char *str);
size_t	get_time(void);
int		usleep_mod(size_t milliseconds);

//philo.c
int		create_threads(t_data *data);
void	*monitoring(void *pointer);
int		check_if_all_ate(t_philo *philos);
int		check_if_dead(t_philo *philos);
int		philosopher_dead(t_philo *philo, size_t time_to_die);
void	destroy_threads(char *message, t_data *data, pthread_mutex_t *forks);

//actions.c
void	*routine(void *pointer);
void	print_message(char *message, t_philo *philo);
//int		dead(t_philo *philo);

#endif