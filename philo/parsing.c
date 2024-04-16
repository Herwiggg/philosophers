/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:52 by almichel          #+#    #+#             */
/*   Updated: 2024/04/16 18:16:17 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_arg_and_pars(char **str)
{
	int	i;

	i = 1;
	
	while (str[i])
	{
		if (ft_check_nbrs(str[i]) == -1)
			return (-1);
		i++;
	}
	i = 1;
	while (str[i])
	{
		if (ft_atoi(str[i]) > 2147483647)
			return (-1);
		i++;
	}
	return (1);
}

int	ft_check_nbrs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

void	ft_init_struct(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
}
