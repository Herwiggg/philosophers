/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:32:41 by almichel          #+#    #+#             */
/*   Updated: 2024/06/27 01:31:23 by almichel         ###   ########.fr       */
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
	if (gettimeofday(&tv, NULL));
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
	
	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break;
		elapsed = gettime(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(usec / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}
