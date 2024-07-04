/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:15 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/04 15:15:11 by pikkak           ###   ########.fr       */
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
	int		i;
	
	i = 1;
	if(argc < 5 || argc > 6)
		printf("Wrong amount of arguments");
	if (argv[1] > 200)
		error("Too many philosophers");
	while (argv[i])
	{
		if (argv[i] <= 0)
			error("Argument too small");
		i++;
	}
	i = 0;
	init_data(&data, argv);
}
