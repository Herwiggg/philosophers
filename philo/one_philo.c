/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 03:10:35 by almichel          #+#    #+#             */
/*   Updated: 2024/07/03 03:24:09 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	dinner_one_philo(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = gettime(MILLISECOND);
	if (pthread_create(&table->philos[0].thread_id, NULL, one_philo,
			&table->philos[0]) != 0)
	{
		while (++i < table->num_of_philos)
		{
			pthread_mutex_destroy(&table->forks[i].fork);
			pthread_mutex_destroy(&table->philos[i].philo_mutex);
		}
		pthread_mutex_destroy(&table->table_mutex);
		pthread_mutex_destroy(&table->write_mutex);
		free(table->philos);
		free(table->forks);
		return (-1);
	}
	return (0);
}

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	increase_long(&philo->table->table_mutex, &philo->table->thread_running);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}
