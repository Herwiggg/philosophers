/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:50:27 by almichel          #+#    #+#             */
/*   Updated: 2024/07/03 20:50:47 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	philo;
	int		i;

	i = -1;
	if (ac != 5 && ac != 6)
		return (write(2, "Wrong number of args\n", 22));
	if (ft_check_arg_and_pars(av) == -1)
		return (write (2, "invalid args\n", 14));
	if (ft_atoi(av[1]) == 0)
		return (write(2, "wrong number of philo\n", 22));
	if (ft_init_struct(&table, av, &philo) == -1)
		return (write(2, "init error\n", 11));
	if (dinner_start(&table, i) == 1)
		return (write(2, "thread error\n", 14));
	pthread_detach(table.monitor);
	destroy_all(&table);
}
