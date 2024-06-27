/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:39:23 by almichel          #+#    #+#             */
/*   Updated: 2024/06/27 02:22:47 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

void	write_status(t_status status, t_philo *philo)
{
	long elapsed;
	if (philo->full)
		return;
	elapsed = gettime(MILLISECOND) - philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_mutex);

	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !simulation_finished(philo->table))
		printf("%-6ld %d has taken a fork", elapsed, philo->id);
	else if ((status == EATING) && !simulation_finished(philo->table))
		printf("%-6ld %d is eating", elapsed, philo->id);
	else if ((status == SLEEPING) && !simulation_finished(philo->table))
		printf("%-6ld %d is sleeping", elapsed, philo->id);
	else if ((status == THINKING) && !simulation_finished(philo->table))
		printf("%-6ld %d is thinking", elapsed, philo->id);
	else if ((status == DIED) && !simulation_finished(philo->table))
		printf("%-6ld %d died", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
