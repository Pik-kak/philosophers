/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:36 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/19 15:17:20 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->drink_poison == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	print_message(char *message, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start;
	if (!dead(philo))//should here be a check for the philos status alive/dead and if yes, why?
		printf("%d %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(philo->write_lock);
}

void	nap(t_philo *philo)
{
	print_message("is sleeping", philo);
	usleep(*philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);//take/LOCK first fork
	print_message("has taken a fork", philo);
	if (*philo->philos_count == 1)
	{
		usleep(*philo->time_to_die);
		print_message("has died", philo);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);//take/lock second fork
	print_message("has taken a fork", philo);
	pthread_mutex_lock(philo->meal_lock);//here is the protected part that cannot be interrupted
	philo->eating = 1;
	print_message("is eating", philo);
	philo->last_ate = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meal_lock);
	usleep(*philo->time_to_eat);
	philo->eating = 0;//should this be inside a meal_lock?
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *pointer)//this is the routine the philo-threads call
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(1);
	while (!dead(philo))
	{
		eat(philo);
		nap(philo);
		print_message("is thinking", philo);
	}
	return (pointer);
}