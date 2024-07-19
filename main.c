/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:15 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/19 18:11:57 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->philos_count)
	{
		philos[i].id = i + 1;
		philos[i].philos_count = &data->philos_count;
		philos[i].time_to_die = &data->time_to_die;
		philos[i].time_to_sleep = &data->time_to_sleep;
		philos[i].time_to_eat = &data->time_to_eat;
		philos[i].eating = 0;
		philos[i].start = get_time();
		philos[i].last_ate = get_time();
		philos[i].meals = &data->meals;
		philos[i].meals_count = 0;
		philos[i].drink_poison = &data->drink_poison;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].write_lock = &data->meal_lock;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[data->philos_count - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;	
	}
}

void	init_forks(pthread_mutex_t *forks, int philos)
{
	int	i;

	i = 0;
	while (i < philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_data(t_data *data, t_philo *philos, char **argv, pthread_mutex_t *forks)
{
	data->philos_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->meals = ft_atoi(argv[5]);
	else
		data->meals = -1;
	data->drink_poison = 0;
	data->philosophers = philos;
	data->forks = forks;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

int main(int argc, char **argv)
{
	t_data			data;//data struct
	t_philo			philos[PHILOS_MAX];//philosophers
	pthread_mutex_t	forks[PHILOS_MAX];//forks
	
	if (check_args(argc, argv) == 1)//check args. What should this return?
		return (0);
	else
	{
		init_forks(forks, ft_atoi(argv[1]));
		init_data(&data, philos, argv, forks);
		init_philos(philos, &data, forks);
		create_threads(&data);//should this return something?
	}
	return (0);
}

