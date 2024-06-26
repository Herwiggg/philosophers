/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:50:27 by almichel          #+#    #+#             */
/*   Updated: 2024/07/02 04:24:58 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_table table;
	t_philo	philo;

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong number of args\n", 22));
	if (ft_check_arg_and_pars(av) == -1)
		return (write (2, "invalid args\n", 14));
	if (ft_atoi(av[1]) == 0)
		return (write(2, "wrong number of philo\n", 22));
	if (ft_init_struct(&table, av, &philo) == -1)
		return (write(2, "init error", 11));
	dinner_start(&table);
	destroy_all(&table);
}
