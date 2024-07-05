/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:23:52 by pikkak            #+#    #+#             */
/*   Updated: 2024/07/05 13:27:28 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int error(char *message)
{
	printf("Error: %s\n" message);
	exit ();	
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
		if (c >= '0' && c <= '9')
			return (1);
		i++;
	}
	return (0);
}

void	check_args(char **args)
{
	int	i;

	i = 1;
	if (argv[1] > PHILOS_MAX)
		error("Too many philosophers\n");
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