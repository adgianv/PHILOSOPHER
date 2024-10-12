#include "philo.h"

pthread_t	*start(t_conf *conf, t_phil *phil, int num_philos)
{
	pthread_t	*threads;
	int			i;

	i = -1;
	conf->start_time = now_ts() + (conf->num_philos * 3);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * num_philos);
	while (++i < num_philos)
	{
		phil[i].last_meal = conf->start_time;
		pthread_create(&threads[i], NULL, &phil_routine, &phil[i]);
	}
	return (threads);
}

int	ft_close(t_conf *c, t_phil *p, pthread_t *t, char *msg)
{
	int	i;

	if (t)
		free(t);
	if (p)
		destroy_mutexes(p[0].forks, p, c->num_philos);
	if (msg)
	{
		i = -1;
		while (msg[++i])
			continue ;
		write(1, msg, i);
	}
	return (1);
}

void	start_checker_routine(t_conf *conf, t_phil *phil, pthread_t *threads)
{
	pthread_t	checker;
	int			i;
	t_data		data;

	i = -1;
	data.config = conf;
	data.philos = phil;
	pthread_create(&checker, NULL, &checker_routine, &data);
	while (++i < conf->num_philos)
		pthread_join(threads[i], NULL);
	i = -1;
	pthread_join(checker, NULL);
}

int	main(int argc, char *argv[])
{
	t_phil					*phil;
	pthread_mutex_t			*forks;
	t_conf					conf;
	pthread_t				*threads;

	if (argc < 5)
		return (ft_close(NULL, NULL, NULL, "More arguments required.\n"));
	else if (argc > 6)
		return (ft_close(NULL, NULL, NULL, "Too many arguments.\n"));
	if (parser(&conf, argc, argv))
		return (ft_close(&conf, NULL, NULL, "Error parsing arguments.\n"));
	phil = (t_phil *)malloc(conf.num_philos * sizeof(t_phil));
	if (!phil)
		return (ft_close(&conf, NULL, NULL, "Memory allocation error (phil).\n"));
	forks = malloc(conf.num_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (ft_close(&conf, NULL, NULL, "Memory allocation error (forks).\n"));
	create_philos(&conf, phil, forks);
	threads = start(&conf, phil, conf.num_philos);
	start_checker_routine(&conf, phil, threads);
	return (ft_close(&conf, phil, threads, NULL));
}
