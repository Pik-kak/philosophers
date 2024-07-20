/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:07 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/20 22:28:01 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_threads(char *message, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (message)
		printf("%s\n", message);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_ate >= time_to_die && philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < *philos[0].philos_count)
	{
		if (philosopher_dead(&philos[i], *philos[i].time_to_die))
		{
			print_message("has died", &philos[i]);
			pthread_mutex_lock(philos[i].dead_lock);
			*philos->drink_poison = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_meal_count(t_philo *philos)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (*philos[0].meals == -1)
		return (0);
	while (i < *philos[0].philos_count)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_count >= *philos[i].meals)
			full++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (full == *philos[0].philos_count)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->drink_poison = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *pointer)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)pointer;
	while (1)
	{
		if (check_if_dead(philosophers) == 1 || check_meal_count(philosophers) == 1)
			break ;
	}
	return (pointer);
}

int	create_threads(t_data *data)
{
	pthread_t	monitor;
	int			i;
	
	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, data->philosophers) != 0)
		destroy_threads("Error in creating monitor thread", data, data->forks);
	while (i < data->philos_count)//create philos
	{
		if(pthread_create(&data->philosophers[i].thread, NULL, &routine, &data->philosophers[i]) != 0)
			destroy_threads("Error in creating philosopher thread", data, data->forks);
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		destroy_threads("Error in joining monitor thread", data, data->forks);
	while (i < data->philos_count)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
			destroy_threads("Error in joining threads", data, data->forks);
		i++;
	}
	return (0);
}
