/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:23:52 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/19 14:52:17 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// Gets the current time in milliseconds

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void error(char *message)//can we use exit?
{
	printf("Error: %s\n", message);
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

int	ft_isdigit(char *arg)//if there is a minus this returns 1
{
	int i;
	
	i = 0;
	while (arg[i] != '\0')
	{
		if (i >= '0' && i <= '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		error("Wrong amount of arguments");
		return (1);
	}
	else if (ft_atoi(argv[1]) > PHILOS_MAX)
	{
		error("Too many philosophers\n");
		return (1);
	}
	else
	{
		while (argv[i])
		{
			if (ft_isdigit(argv[i]) == 1)//doesn't this already check if there is a minus?
				error("Wrong type of argument\n");
			if (i < 5 && ft_atoi(argv[i]) <= 0)
				error("Argument too small\n");
			if (i == 5 && ft_atoi(argv[i]) < 0)//the last argument
				error("Argument too small\n");
			i++;
		}
	}
	return (0);
}
