#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>

typedef struct s_philo
{
	//	pthread_t		thread;
	int		id;
	int		eating;
	int		meals_eaten;
	int		last_meal;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		start_time;
	int		num_of_philos;
	int		num_times_to_eat;
	int		*dead;
	//	pthread_mutex_t	*r_fork;
	//	pthread_mutex_t	*l_fork;
	//	pthread_mutex_t	*write_lock;
	//	pthread_mutex_t	*dead_lock;
	//	pthread_mutex_t	*meal_lock;
}			t_philo;

/*---------Parsing-----------*/
int			ft_check_arg_and_pars(char **str);
int			ft_check_nbrs(char *str);
void		ft_init_struct(t_philo *philo, char **argv);

/*---------Utils-----------*/
long long	ft_atoi(const char *nptr);

#endif