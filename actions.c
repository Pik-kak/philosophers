/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:36 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/06 13:52:07 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 Extra monitor thread checks constantly that a philo is alive and they have not yet eaten enough.
 It checks that the time a philo needs to die didn’t surpass the last meal he had and that he is not concurrently eating.
 If he indeed died we change the dead flag to 1 and that will break the loop in all of the threads. 
 The other check is to see if all the philos finished eating the amount of meals they need to, and if they did we will again change the dead flag to one and break the threads loop.
*/
void	monitoring()
{

}

void	eat(t_philo *philo)
{
	
}

void	sleep(t_philo *philo)
{
	
}

void	think(t_philo *philo)
{
	
}

void	routine()//this is the routine the philo-threads call
{
	
}