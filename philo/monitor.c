/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 03:39:50 by almichel          #+#    #+#             */
/*   Updated: 2024/06/30 05:17:52 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
//	printf("%ld\n", philo->last_meal_time);
	elapsed = (gettime(MICROSECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time));
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table *table;
	int		i;
	
	table = (t_table *)data;
	while (!all_thread_running(&table->table_mutex, &table->thread_running, table->num_of_philos))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->num_of_philos && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
			}
		}
	}

	return (NULL);
}
