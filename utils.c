/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:23:52 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/20 23:08:39 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	usleep_mod(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error in gettimeofday()\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static int	count_signs(const char *s, int i)
{
	if ((s[i] == 43 || s[i] == 45) && (s[i + 1] == 43 || s[i + 1] == 45))
		return (0);
	if (s[i] == 45)
		return (1);
	if (s[i] == 43)
		return (2);
	return (3);
}

int	ft_atoi(const char *str)
{
	int		signs;
	long	result;
	int		i;
	long	prev;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	signs = count_signs(str, i);
	if (signs == 0)
		return (0);
	if (signs == 1 || signs == 2)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		prev = result;
		result = result * 10 + (str[i] - 48);
		i++;
		if (prev > result)
			return (-1);
	}
	if (signs == 1)
		return (-result);
	return (result);
}

static int	ft_isdigit(char *argv)//if there is a minus or  Something is wrong here
{
	int i;
	
	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 1 || ft_atoi(argv[i]) <= 0)//doesn't this already check if there is a minus?
		{
			printf("Wrong type of argument\n");
			return (1);
		}
		i++;
	}
	if (ft_atoi(argv[1]) > PHILOS_MAX)
	{
		printf("Too many philosophers\n");
		return (1);
	}
	return (0);
}
