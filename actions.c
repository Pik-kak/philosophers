/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:36 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/22 15:25:28 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dead(t_philo *philo)
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
	if (!dead(philo))
		printf("%d %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(philo->write_lock);
}

static void	nap(t_philo *philo)
{
	print_message("is sleeping", philo);
	usleep_mod(*philo->time_to_sleep);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken a fork", philo);
	if (*philo->philos_count == 1)
	{
		usleep_mod(*philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork", philo);
	print_message("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_ate = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	usleep_mod(*philo->time_to_eat);
	philo->meals_count++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep_mod(*philo->time_to_eat);
	while (dead(philo) != 1)
	{
		eat(philo);
		nap(philo);
		print_message("is thinking", philo);
	}
	return (pointer);
}
