/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:50:27 by almichel          #+#    #+#             */
/*   Updated: 2024/06/28 18:28:51 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_table table;
	t_philo	philo;

	if (ac != 5 && ac != 6)
	{
		write(1, "Wrong number of args\n", 22);
		return (-1);
	}
	if (ft_check_arg_and_pars(av) == -1)
	{
		write (1, "invalid args\n", 14);
		return (-1);
	}
	ft_init_struct(&table, av, &philo);
	dinner_start(&table);
	//dinner_simulation(&philo);
}
