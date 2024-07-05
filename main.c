/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:15 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/05 12:02:41 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(struct t_data *data, char **argv)
{
	data->philos = argv[1];
	data->time_to_die = argv[2];
	data->time_to_eat = argv[3];
	data->time_to_sleep = argv[4];
	if (argv[5] != NULL)
		data->meals = argv[5];
}

int main(int argc, char **argv)
{
	t_data	*data;
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
}
