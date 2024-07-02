/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:49:07 by almichel          #+#    #+#             */
/*   Updated: 2024/07/02 23:55:54 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define BLUE "\033[1;34m"
# define RST "\033[0m"

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
	bool				full;
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
int						ft_init_struct(t_table *table, char **argv,
							t_philo *philo);
int						ft_init_struct_2(t_table *table);
void					assign_fork(t_philo *philo, t_fork *forks, int i);
int						init_philo(t_philo *philo, t_table *table);

/*---------Dinner----------*/
int						dinner_start(t_table *table);
void					*dinner_simulation(void *data);
void					wait_threads(t_table *table);
void					write_status(t_status status, t_philo *philo);
bool					simulation_finished(t_table *table);
void					eat(t_philo *philo);
void					sleeping(t_philo *philo);
void					think(t_philo *philo);

/*---------Monitor----------*/
void					*monitor_dinner(void *data);
bool					philo_died(t_philo *philo);

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
bool					all_thread_running(pthread_mutex_t *mutex, long *thread,
							long philo_nbr);

/*---------Errors & free-----------*/
int						destroy_all(t_table *table);
int						destroy_error_mutex(t_table *table, int type, int type2,
							int type3);
void					destroy_error_mutex_2(t_table *table, int type3);
int						destroy_error_thread(t_table *table, int type, int nbr);

#endif