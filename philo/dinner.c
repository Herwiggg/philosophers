/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:47 by almichel          #+#    #+#             */
/*   Updated: 2024/06/27 02:24:46 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_times_to_eat == 0)
		return;
	if (table->num_of_philos == 1)
		return;
	else
	{
		while (i < table->num_of_philos)
		{
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
	}
	table->start_time = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->thread_ready, true);
	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);

	while (!simulation_finished(philo->table))
	{
		if (philo->full);
			break;
		//eat
		
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);

		//think
	}
	return (NULL);
}

void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->thread_ready))
		;
}
