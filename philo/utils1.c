/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:32:41 by almichel          #+#    #+#             */
/*   Updated: 2024/07/05 03:54:04 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (0);
}

unsigned int	time_for_usleep(void)
{
	struct timeval	time;
	unsigned int	time_return;

	gettimeofday(&time, NULL);
	time_return = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time_return);
}

void	ft_usleep(int action_time)
{
	unsigned int	start_time;

	start_time = time_for_usleep();
	while (time_for_usleep() - start_time < (unsigned int)action_time)
		usleep(200);
}

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->thread_ready))
		;
}
