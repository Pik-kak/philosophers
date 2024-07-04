/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:19:59 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/04 14:57:14 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
	int	id;
	int	last_ate;
	int	meals_count;
	
	
}			t_philo;

typedef struct s_data
{
	int			philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals;
	t_philo		*philosophers;
}			t_data;

#endif