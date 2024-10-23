#include "philo.h"

void    populate_config(t_conf *config, char *argv[], int argc)
{
    config->stop = false;
	config->num_philos = ft_atoi(argv[1]);
	config->die_time = ft_atoi(argv[2]);
	config->eat_time = ft_atoi(argv[3]);
	config->sleep_time = ft_atoi(argv[4]);
	config->meals_till_full = -1;
	if (argc == 6)
		config->meals_till_full = ft_atoi(argv[5]);
}

void    populate_philos(t_conf *config, t_phil *philos, 
                        pthread_mutex_t *forks, int i)
{
    philos[i].forks = forks;
    philos[i].id = i + 1;
    philos[i].fork_ids[0] = i;
    philos[i].fork_ids[1] = (i + 1) % config->num_philos;
    philos[i].num_meals = 0;
    philos[i].full = false;
    philos[i].config = config;
}

void    print_message(int id, char *act, t_conf *conf, bool d)
{
	if (d)
		return ;
	pthread_mutex_lock(&conf->lock_print);
	printf("%lld %d %s\n", (now_ts() - conf->start_time), id, act);
	pthread_mutex_unlock(&conf->lock_print);
	return ;
}

void    destroy_mutexes(pthread_mutex_t *forks, t_phil *philos, int num_philos)
{
	int	i;

	i = -1;
	while (++i < num_philos)
	{
		pthread_mutex_destroy(&philos[i].lock_rw);
		pthread_mutex_destroy(&forks[i]);
	}
	free(forks);
	free(philos);
}

bool    is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (true);
    else
        return (false);
}
