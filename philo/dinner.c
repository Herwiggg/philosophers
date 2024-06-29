/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:47 by almichel          #+#    #+#             */
/*   Updated: 2024/06/29 19:03:52 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->num_times_to_eat > 0 && philo->meals_counter == philo->table->num_times_to_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}
void think(t_philo *philo)
{
	write_status(THINKING, philo);
}

void	sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

void	dinner_start(t_table *table)
{
	int	i;
	i = -1;
	if (table->num_times_to_eat == 0)
		return;
	if (table->num_of_philos == 1)
		return;
	else
	{
		while (++i < table->num_of_philos)
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
	}
	table->start_time = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->thread_ready, true);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philos[i].thread_id, NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break;
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->thread_ready))
		;
}
