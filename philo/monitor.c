/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 03:39:50 by almichel          #+#    #+#             */
/*   Updated: 2024/07/04 02:15:57 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	all_thread_running(pthread_mutex_t *mutex, long *threads, long nbr)
{
	bool	retur;

	retur = false;
	pthread_mutex_lock(mutex);
	if (nbr == *threads)
		retur = true;
	pthread_mutex_unlock(mutex);
	return (retur);
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = (gettime(MILLISECOND) - get_long(&philo->philo_mutex,
				&philo->last_meal_time));
	time_to_die = philo->table->time_to_die;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;
	int		flag_all_full;
	
	table = (t_table *)data;
	while (all_thread_running(&table->table_mutex, &table->thread_running,
			table->num_of_philos) == false)
		;
	while (!simulation_finished(table))
	{
		i = -1;
		flag_all_full = 0;
		while (++i < table->num_of_philos && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				write_status(DIED, table->philos + i);
				set_bool(&table->table_mutex, &table->end_simulation, true);
				break ;
			}
			if  (is_full(table->philos + i) == 0)
				flag_all_full++;
			if (flag_all_full == table->num_of_philos)
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
			}
		}
		
	}
	return (NULL);
}
/*
int	check_number_eat(t_table *table)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	while (++i < table->num_of_philos)
	{
		//pthread_mutex_lock(&table->philo->check_eat_mutex);
		if (is_full(table->philo + i) == 0)
		{
			flag++;
		//	pthread_mutex_unlock(&table->philo->check_eat_mutex);
			return (-1);
		}
		if (flag == table->num_of_philos)
			return (1);
		//pthread_mutex_unlock(&table->philo->check_eat_mutex);
		i++;
	}
	return (1);
}*/

int		is_full(t_philo *philo)
{
	if (philo->full == true)
		return (0);
	return (1);
}
