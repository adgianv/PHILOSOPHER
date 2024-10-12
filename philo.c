#include "philo.h"

int	control_philos(t_phil *philos, t_conf *config)
{
	int	i;
	int	r;

	i = -1;
	r = 1;
	while (++i < config->num_philos)
	{
		if (config->stop)
			break ;
		pthread_mutex_lock(&philos[i].lock_rw);
		if ((int)(now_ts() - philos[i].last_meal) > config->die_time)
		{
			print_message(i + 1, DIE, config, config->stop);
			config->stop = true;
		}
		if (!philos[i].full)
			r = 0;
		pthread_mutex_unlock(&philos[i].lock_rw);
	}
	if (r)
		return (r);
	return (config->stop);
}

void	*checker_routine(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	start_wait(data->config->start_time);
	while (1)
	{
		if (control_philos(data->philos, data->config))
			break ;
		usleep(1000);
	}
	return (0);
}

void	*phil_routine(void *args)
{
	t_phil			*philo;

	philo = (t_phil *)args;
	start_wait(philo->config->start_time);
	if (!(philo->id % 2))
		ft_sleep(200);
	if (philo->config->num_philos == 1)
	{
		print_message(philo->id, THINK, philo->config, philo->config->stop);
		run_one_phil(philo);
		// return ((void *)0);
		return (NULL);
	}
	while (!philo->config->stop)
	{
		print_message(philo->id, THINK, philo->config, philo->config->stop);
		run_phil(philo);
		if (philo->full)
			break ;
	}
	return (NULL);
}

void	create_philos(t_conf *config, t_phil *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < config->num_philos)
	{
		pthread_mutex_init(&philos[i].lock_rw, NULL);
		pthread_mutex_init(&forks[i], NULL);
		populate_philos(config, philos, forks, i);
	}
}
