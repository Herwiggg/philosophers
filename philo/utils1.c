/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:32:41 by almichel          #+#    #+#             */
/*   Updated: 2024/07/01 17:25:47 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10;
		result = result + nptr[i] - 48;
		i++;
	}
	return (sign * result);
}

long	gettime(t_time_code time_code)
{
	struct timeval tv;
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

void	precise_usleep(long usec, t_table *table)
{
	long start;
	long elapsed;
	long remaining;
	
	start = gettime(MILLISECOND);
	while (gettime(MILLISECOND) - start < usec)
	{
		if (simulation_finished(table))
			break;
		elapsed = gettime(MILLISECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (gettime(MILLISECOND) - start < usec)
				;
		}
	}
}

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

bool all_thread_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
	bool retur;

	retur = false;
	pthread_mutex_lock(mutex);
	if (philo_nbr == *threads)
		retur = true;
	pthread_mutex_unlock(mutex);
	return (retur);
}

void	destroy_all(t_table *table)
{
	int	i;
	i = -1;
	//pthread_mutex_destroy(&philo->philo_mutex);
	while (++i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
	}
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->write_mutex);
}
