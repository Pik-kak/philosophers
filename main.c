/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:15 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/20 22:11:05 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_argv(t_data *data, t_philo *philo)
{
		philo->philos_count = &data->philos_count;
		philo->time_to_die = &data->time_to_die;
		philo->time_to_sleep = &data->time_to_sleep;
		philo->time_to_eat = &data->time_to_eat;
		philo->meals = &data->meals;
}

static void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->philos_count)
	{
		init_argv(data, &philos[i]);
		philos[i].id = i + 1;
		philos[i].start = get_time();
		philos[i].last_ate = get_time();
		philos[i].eating = 0;
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

static void	init_data(t_data *data, t_philo *philos, char **argv, pthread_mutex_t *forks)
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

static void	init_forks(pthread_mutex_t *forks, int philos)
{
	int	i;

	i = 0;
	while (i < philos)
	{
		pthread_mutex_init(&forks[i], NULL);//should we protect this?
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];
	
	if (argc < 5 || argc > 6)
	{
		printf("Wrong amount of arguments\n");
		return (1);
	}
	if (check_args(argv) == 1)
		return (1);
	init_forks(forks, ft_atoi(argv[1]));
	init_data(&data, philos, argv, forks);
	init_philos(philos, &data, forks);
	if (create_threads(&data) == 1)
		return (1);
	destroy_threads(NULL, &data, forks);
	return (0);
}

