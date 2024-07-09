/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:15 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/09 14:46:43 by pikkak           ###   ########.fr       */
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
		philos[i].eating = 0;
		philos[i].start = get_current_time();
		philos[i].last_ate = get_current_time();
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

void	init_data(struct t_data *data, struct t_philo *philos, char **argv)
{
	data->philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->meals = ft_atoi(argv[5]);
	else
		data->meals = -1;
	data->drink_poison = 0;
	data->philos = philos;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

int main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[PHILOS_MAX]
	pthread_mutex_t	forks[PHILOS_MAX]
	int				i;
	
	i = 0;
	if(argc < 5 || argc > 6)//return 1
		error("Wrong amount of arguments");
	else if (check_args(args) == 1)//return 1
		error("Wrong amount of arguments");
	else
	{
		init_data(&data, philos, argv);
		init_forks(forks, ft_atoi(argv[1]));
		init_philos(&philos, &data, forks);
		create_threads(&data, forks);//should this return something?
	}
	return (0);
}

