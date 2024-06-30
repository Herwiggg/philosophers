
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:49:07 by almichel          #+#    #+#             */
/*   Updated: 2024/06/26 04:19:30 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_philo	t_philo;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_status;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_time;
	long				num_of_philos;
	long				num_times_to_eat;
	bool				end_simulation;
	bool				thread_ready;
	long				thread_running;
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
	pthread_t			monitor;
}						t_table;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool					full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	pthread_mutex_t		philo_mutex;
	t_table				*table;

}						t_philo;

/*---------Parsing & Init-----------*/
int						ft_check_arg_and_pars(char **str);
int						ft_check_nbrs(char *str);
void					ft_init_struct(t_table *table, char **argv,
							t_philo *philo);
void					assign_fork(t_philo *philo, t_fork *forks, int i);
void					init_philo(t_philo *philo, t_table *table);

/*---------Dinner----------*/
void					dinner_start(t_table *table);
void					*dinner_simulation(void *data);
void					wait_threads(t_table *table);
void					write_status(t_status status, t_philo *philo);
bool					simulation_finished(t_table *table);
void 					eat(t_philo *philo);
void					sleeping(t_philo *philo);
void 					think(t_philo *philo);

/*---------Dinner----------*/
void	*monitor_dinner(void *data);
bool	philo_died(t_philo *philo);

/*---------setters & getters-----------*/
void					set_bool(pthread_mutex_t *mutex, bool *dest,
							bool value);
bool					get_bool(pthread_mutex_t *mutex, bool *value);
void					set_long(pthread_mutex_t *mutex, long *dest,
							long value);
long					get_long(pthread_mutex_t *mutex, long *value);

/*---------Utils-----------*/
long long				ft_atoi(const char *nptr);
long					gettime(t_time_code time_code);
void					precise_usleep(long usec, t_table *table);
void					increase_long(pthread_mutex_t *mutex, long *value);
bool 					all_thread_running(pthread_mutex_t *mutex, long *thread, long philo_nbr);

#endif