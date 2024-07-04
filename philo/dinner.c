/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:47 by almichel          #+#    #+#             */
/*   Updated: 2024/07/04 20:42:06 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	write_status(EATING, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->num_times_to_eat > 0
		&& philo->meals_counter == philo->table->num_times_to_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}


void	sleeping_thinking(t_philo *philo)
{
	write_status(SLEEPING, philo);
	precise_usleep(philo->table->time_to_sleep, philo->table);
	write_status(THINKING, philo);
}

int	dinner_start(t_table *table, int i)
{
	if (table->num_times_to_eat == 0)
		return (0);
	if (table->num_of_philos == 1)
	{
		if (dinner_one_philo(table) == -1)
			return (-1);
	}
	else
	{
		table->start_time = gettime(MILLISECOND);
		while (++i < table->num_of_philos)
			if (pthread_create(&table->philos[i].thread_id, NULL,
					dinner_simulation, &table->philos[i]) != 0)
				return (destroy_error_thread(table, 0, i));
	}
	if (pthread_create(&table->monitor, NULL, monitor_dinner, table) != 0)
		return (destroy_error_thread(table, 2, table->num_of_philos));
	set_bool(&table->table_mutex, &table->thread_ready, true);
	i = -1;
	while (++i < table->num_of_philos)
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			return (destroy_error_thread(table, 2, table->num_of_philos));
	return (0);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->thread_running);
	if (philo->id % 2 == 0)
		precise_usleep(philo->table->time_to_eat, philo->table);
	while (!simulation_finished(philo->table))
	{
		eat(philo);
		sleeping_thinking(philo);
	}
	return (NULL);
}
