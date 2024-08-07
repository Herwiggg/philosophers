/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:39:23 by almichel          #+#    #+#             */
/*   Updated: 2024/07/05 16:48:12 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	if (simulation_finished(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	elapsed = gettime(MILLISECOND) - philo->table->start_time;
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf("%ld %d has taken a fork\n", elapsed, philo->id + 1);
	else if ((status == EATING) && !simulation_finished(philo->table))
		printf("%ld %d is eating\n", elapsed, philo->id + 1);
	else if ((status == SLEEPING) && !simulation_finished(philo->table))
		printf("%ld %d is sleeping\n", elapsed, philo->id + 1);
	else if ((status == THINKING) && !simulation_finished(philo->table))
		printf("%ld %d is thinking\n", elapsed, philo->id + 1);
	else if ((status == DIED) && !simulation_finished(philo->table))
		printf("%ld %d died\n", elapsed, philo->id + 1);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
