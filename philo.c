/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:07 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/19 15:20:58 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Destroys all the mutexes

void	destroy_threads(char *message, t_data *data, pthread_mutex_t *forks)//should this exit?
{
	int	i;

	i = 0;
	if (message)
		printf("%s\n", message);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->philos_count)//destroy forks
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

// Checks if the philosopher is dead

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

// Check if any philo died

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < *philos[0].philos_count)
	{
		if (philosopher_dead(&philos[i], *philos[i].time_to_die))
		{
			print_message("died", &philos[i]);
			pthread_mutex_lock(philos[i].dead_lock);
			*philos->drink_poison = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if all the philos ate the num_of_meals

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (*philos[0].meals == -1)//if there is no meal count given as argument
		return (0);
	while (i < *philos[0].philos_count)
	{
		pthread_mutex_lock(philos[i].meal_lock);//put on meal lock
		if (philos[i].meals_count >= *philos[i].meals)//if the philo has eaten enough meals we mark it as finished
			full++;
		pthread_mutex_unlock(philos[i].meal_lock);//unlock mutex and move onto the next philo
		i++;
	}
	if (full == *philos[0].philos_count)//check if all have eaten enough
	{
		pthread_mutex_lock(philos[0].dead_lock);//put on dead lock and set dead flag to 1 
		*philos->drink_poison = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}


// Extra monitor thread checks constantly that a philos is alive and they have not yet eaten enough.
// It checks that the time a philo needs to die didn’t surpass the last meal he had and that he is not concurrently eating.
// If he indeed died we change the dead flag to 1 and that will break the loop in all of the threads. 
// The other check is to see if all the philos finished eating the amount of meals they need to, and if they did we will again change the dead flag to one and break the threads loop.

void	*monitoring(void *pointer)
{
	t_philo *philosophers;

	philosophers = (t_philo *)pointer;
	while (1)
	{
		if (check_if_dead(philosophers) == 1 || check_if_all_ate(philosophers) == 1)
			break ;
	}
	return (pointer);
}

int	create_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;
	
	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, data->philosophers) != 0)//create monitor
		destroy_threads("Error in creating monitor thread", data, forks);
	while (i < data->philos_count)//create philos
	{
		if(pthread_create(&data->philosophers[i].thread, NULL, &routine, data->philosophers) != 0)
			destroy_threads("Error in creating philosopher thread", data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		destroy_threads("Error in joining monitor thread", data, forks);
	while (i < data->philos_count)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
			destroy_threads("Error in joining threads", data, forks);
		i++;
	}
	return (0);
}
