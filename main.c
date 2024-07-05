/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:15 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/05 13:39:17 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->philos_count)
	{
		philos[i]->id = 
		philos[i]->last_ate =
		philos[i]->meals_count =
		philos[i]->dead =

		i++;	
	}
}

void	init_data(struct t_data *data, char **argv)
{
	data->philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->meals = ft_atoi(argv[5]);
	else
		data->meals = -1;
}

int main(int argc, char **argv)
{
	t_data	data;
	t_philo	philos[PHILOS_MAX]
	pthread_mutex_t	forks[PHILOS_MAX]
	int		i;
	
	i = 1;
	if(argc < 5 || argc > 6)
		printf("Wrong amount of arguments");
	if (check_args(args) == 1)
		return (1);
	i = 0;
	init_data(&data, argv);
	init_philos(&philos, &data, &forks);
}
