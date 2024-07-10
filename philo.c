/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:07 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/10 15:30:46 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *message, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(*philo->write_lock)
	time = (get_current_time() - philo->start_time);//should here be a check for the philos status alive/dead and if yes, why?
	printf("%d %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(*philo->write_lock);
}

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
