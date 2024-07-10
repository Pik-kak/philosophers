/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:36 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/10 15:19:45 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->right_fork);//take/LOCK first fork
	print_message("has taken a fork");
	if (data->philos_count == 1)
	{
		usleep(data->time time_to_die);
		print_message("has died");
		pthread_mutex_unlock(right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);//take/lock second fork
	print_message("has taken a fork");
	pthread_mutex_lock(philo->meal_lock);//here is the protected part that cannot be interrupted
	philo->eating = 1;
	print_message("is eating");
	philo->last_ate = get_current_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meal_lock);
	usleep(data->time_to_eat);
	philo->eating = 0;//should this be inside a meal_lock?
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep(t_philo *philo, t_data *data)
{
	print_message("is sleeping");
	usleep(data->time_to_sleep);
}

void	think(t_philo *philo)//do we need a function for this?
{
	print_message("is thinking");
}


int	dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->drink_poison == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0;)
}

void	*routine(void *pointer)//this is the routine the philo-threads call
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(1);
	while (!dead(philo))
	{
		eat(philo);
		sleep(philo);
		think(philo);
	}
	return (pointer);
}