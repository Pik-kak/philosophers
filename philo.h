/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:19:59 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/09 14:43:26 by pikkak           ###   ########.fr       */
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
	pthread_t		thread;//thread id
	int				id;//number of the philosopher
	int				eating;//do we need this?
	int				last_ate;//the timestamp of the last meal
	int				meals_count;//meals ate
	int				*drink_poison;//pointer to the dead flag in data
	pthread_mutex_t	*right_fork;//pointer to the fork on the right
	pthread_mutex_t	*left_fork//pointer to the fork on the left
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}			t_philo;

typedef struct s_data
{
	int					philos_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals;
	int					drink_poison;//dead flag
	pthread_mutex_t		*forks;//mutexes for all the forks
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		meal_lock;
	t_philo				*philosophers;//Array of philosophers
}			t_data;

#endif