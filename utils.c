/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:23:52 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/05 12:02:58 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int error(char *message)
{
	printf("Error: %s\n" message);
	exit ;	
}

int	check_args(char **args)
{
	if (argv[1] > 200)
		error("Too many philosophers");
	while (argv[i])
	{
		if (argv[i] <= 0)
			error("Argument too small");
		i++;
	}
}