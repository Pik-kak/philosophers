/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:19:59 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/05 13:34:09 by kkauhane         ###   ########.fr       */
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
	p_thread_t		thread;
	int				id;
	int				last_ate;
	int				meals_count;
	int				dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork
}			t_philo;

typedef struct s_data
{
	int					philos_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals;
	pthread_mutex_t		*forks;
	t_philo				*philosophers;
}			t_data;

#endif