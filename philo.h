#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIE "died"
# define FORK_TAKEN "has taken a fork"

typedef struct s_conf
{
	unsigned long long		start_time;
	int						num_philos;
	int						die_time;
	int						sleep_time;
	int						eat_time;
	bool					stop;
	int						meals_till_full;
	pthread_mutex_t			lock_print;
}	t_conf;

typedef struct s_phil
{
	int						id;
	bool					full;
	int						num_meals;
	int						fork_ids[2];
	unsigned long long		last_meal;
	pthread_mutex_t			lock_rw;
	pthread_mutex_t			*forks;
	t_conf					*config;
}	t_phil;

typedef struct s_data
{
	t_conf		*config;
	t_phil		*philos;
}	t_data;

int			ft_atoi(const char *str);
int			parser(t_conf *config, int argc, char *argv[]);
void		*checker_routine(void *args);
unsigned long long	now_ts(void);
void		ft_sleep(int ms);
void		*phil_routine(void *arguments);
void		create_philos(t_conf *config,	t_phil *philos,
				pthread_mutex_t *forks);
void		run_one_phil(t_phil *philo);
void		run_phil(t_phil *philo);
void 		populate_philos(t_conf *config, t_phil *philos, pthread_mutex_t *forks, int i);
void 		populate_config(t_conf *config, char *argv[], int argc);
void		start_wait(unsigned long long st);
void		print_message(int id, char *act, t_conf *conf, bool d);
void		print_message(int id, char *act, t_conf *config, bool d);
bool 		is_digit(char c);
void		destroy_mutexes(pthread_mutex_t *forks, t_phil *philos,
				int num_philos);
void		destroy_mutexes(pthread_mutex_t *forks, t_phil *philos, int num_philos);

#endif
