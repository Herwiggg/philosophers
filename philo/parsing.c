/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:52 by almichel          #+#    #+#             */
/*   Updated: 2024/04/17 18:48:20 by almichel         ###   ########.fr       */
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
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

void	ft_init_struct(t_table *table, char **argv, t_philo *philo)
{
	int	i;

	i = 1;
	table->num_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->num_times_to_eat = ft_atoi(argv[5]);
	else
		table->num_times_to_eat = -1;
	table->philos = malloc((ft_atoi(argv[1]) * sizeof(t_fork)));
	if (!table->philos)
		return;
	table->forks = malloc((ft_atoi(argv[1]) * sizeof(t_fork)));
	if (!table->forks)
		return;
	table->end_simulation = -1;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
	init_philo(philo, table);
}

void	init_philo(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		philo = table->philos + i;
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->full = 1; 
		philo->table = table;
		init_fork(philo, table->forks, i);
		i++;
	}
}

void	init_fork(t_philo *philo, t_fork *forks, int i)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo->table->num_of_philos];
	}
	else
	{
		philo->second_fork = &forks[i];
		philo->first_fork = &forks[(i + 1) % philo->table->num_of_philos];
	}

}
