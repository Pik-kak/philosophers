/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:15 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/08 13:56:41 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->philos_count)
	{
		philos[i]->id = i + 1;
		philos[i]->eating = 0;
		philos[i]->start = get_current_time();
		philos[i]->last_ate = get_current_time();
		philos[i]->meals_count = 0;

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
		init_philos(&philos, &data, &forks);//should this make the treads as well?
		while ()
		{
			if (pthread_create(&philos[i], NULL, &routine, NULL) != 0)
				error("Could not create a thread\n");
		}
		while ()
		{
			pthread_join(philos[i], NULL);
		}
	}
	return (0);
}

