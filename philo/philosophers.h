/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:49:07 by almichel          #+#    #+#             */
/*   Updated: 2024/04/17 18:49:08 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* - time_to_die: Time after which a philosopher will die if they haven't eaten.
** - time_to_eat: Time it takes for a philosopher to eat a meal.
** - time_to_sleep: Time it takes for a philosopher to sleep.
** - nbr_limit_meals: The number of meals limit, if < 0 no limits.
** - philo_nbr: Total number of philosophers at the table.
** - start_simulation: The starting time of the simulation.
** - end_simulation: when a philo die, this flag ON
** - all_threads_ready: synchro the start of simulation*/

typedef struct s_philo	t_philo;
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_table
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					start_time;
	int					num_of_philos;
	int					num_times_to_eat;
	int					end_simulation;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	int					full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_table				*table;

}						t_philo;

/*---------Parsing & Init-----------*/
int						ft_check_arg_and_pars(char **str);
int						ft_check_nbrs(char *str);
void					ft_init_struct(t_table *table, char **argv,
							t_philo *philo);
void					init_fork(t_philo *philo, t_fork *forks, int i);
void					init_philo(t_philo *philo, t_table *table);

/*---------Utils-----------*/
long long				ft_atoi(const char *nptr);

#endif