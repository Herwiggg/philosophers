/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:47 by almichel          #+#    #+#             */
/*   Updated: 2024/06/26 04:47:24 by almichel         ###   ########.fr       */
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
	set_bool(&table->table_mutex, &table->thread_ready, true);
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);

	return (NULL);
}

void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->thread_ready))
		;
}
