/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:07 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/09 15:01:06 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 Extra monitor thread checks constantly that a philos is alive and they have not yet eaten enough.
 It checks that the time a philo needs to die didn’t surpass the last meal he had and that he is not concurrently eating.
 If he indeed died we change the dead flag to 1 and that will break the loop in all of the threads. 
 The other check is to see if all the philos finished eating the amount of meals they need to, and if they did we will again change the dead flag to one and break the threads loop.
*/
void	monitoring(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->meals_count)
	return (pointer);
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

int	create_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;
	
	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, data->philosophers) != 0)//create monitor
		destroy_treads();
	while (i < data->philos_count)
	{
		if(pthread_create(&data->philosophers[i].thread, NULL, &routine, data->philosophers[i]) != 0)
			destroy_treads();
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		destroy_treads();
	while (i < data->philos_count)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
			destroy_treads();
		i++;
	}
	return (0);
}
