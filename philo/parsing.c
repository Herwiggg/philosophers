/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:52 by almichel          #+#    #+#             */
/*   Updated: 2024/07/05 03:53:48 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_struct(t_table *table, char **argv, t_philo *philo)
{
	table->num_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->num_times_to_eat = ft_atoi(argv[5]);
	else
		table->num_times_to_eat = -1;
	table->philos = malloc((ft_atoi(argv[1]) * sizeof(t_philo)));
	if (!table->philos)
		return (-1);
	table->forks = malloc((ft_atoi(argv[1]) * sizeof(t_fork)));
	if (!table->forks)
	{
		free(table->philos);
		return (-1);
	}
	if (ft_init_struct_2(table) == -1)
		return (-1);
	return (init_philo(philo, table));
}

int	ft_init_struct_2(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->thread_ready = false;
	table->thread_running = 0;
	table->flag_all_full = 0;
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (destroy_error_mutex(table, 0, 0, 0));
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return (destroy_error_mutex(table, 1, 0, 0));
	while (++i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (destroy_error_mutex(table, 2, i, 0));
		table->forks[i].fork_id = i;
	}
	return (0);
}

int	init_philo(t_philo *philo, t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_init(&philo->check_eat_mutex, NULL);
	while (++i < table->num_of_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->full = false;
		philo->table = table;
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
			return (destroy_error_mutex(table, 3, table->num_of_philos, i));
		assign_fork(philo, table->forks);
	}
	return (0);
}

void	assign_fork(t_philo *philo, t_fork *forks)
{
	if (philo->id == 0)
	{
		philo->first_fork = &forks[philo->table->num_of_philos - 1];
		philo->second_fork = &forks[philo->id];
	}
	else
	{
		philo->second_fork = &forks[philo->id - 1];
		philo->first_fork = &forks[philo->id];
	}
}
