/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:49:37 by almichel          #+#    #+#             */
/*   Updated: 2024/07/02 23:52:00 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
	}
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	free(table->philos);
	free(table->forks);
	return (0);
}

int	destroy_error_mutex(t_table *table, int type, int type2, int type3)
{
	int	i;

	i = -1;
	if (type == 0)
		pthread_mutex_destroy(&table->table_mutex);
	else if (type == 1)
	{
		pthread_mutex_destroy(&table->table_mutex);
		pthread_mutex_init(&table->write_mutex, NULL);
	}
	else if (type == 2)
	{
		pthread_mutex_destroy(&table->table_mutex);
		pthread_mutex_init(&table->write_mutex, NULL);
		while (++i < type2)
			pthread_mutex_destroy(&table->forks[i].fork);
	}
	else if (type == 3)
		destroy_error_mutex_2(table, type3);
	free(table->philos);
	free(table->forks);
	return (-1);
}

void	destroy_error_mutex_2(t_table *table, int type3)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_init(&table->write_mutex, NULL);
	while (++i < table->num_of_philos)
		pthread_mutex_destroy(&table->forks[i].fork);
	i = -1;
	while (++i < type3)
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
}

int	destroy_error_thread(t_table *table, int type, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		pthread_detach(table->philos[i].thread_id);
	if (type >= 2)
		pthread_detach(table->monitor);
	i = -1;
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_init(&table->write_mutex, NULL);
	while (++i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
	}
	free(table->philos);
	free(table->forks);
	return (-1);
}
