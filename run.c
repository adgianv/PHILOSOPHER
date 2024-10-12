#include "philo.h"

void	run_phil(t_phil *philo)
{
	pthread_mutex_lock(&philo->forks[philo->fork_ids[0]]);
	print_message(philo->id, FORK_TAKEN, philo->config, philo->config->stop);
	pthread_mutex_lock(&philo->forks[philo->fork_ids[1]]);
	print_message(philo->id, FORK_TAKEN, philo->config, philo->config->stop);
	print_message(philo->id, EAT, philo->config, philo->config->stop);
	pthread_mutex_lock(&philo->lock_rw);
	(philo->num_meals)++;
	philo->last_meal = now_ts();
	if (philo->num_meals == philo->config->meals_till_full)
		philo->full = true;
	pthread_mutex_unlock(&philo->lock_rw);
	ft_sleep(philo->config->eat_time);
	pthread_mutex_unlock(&philo->forks[philo->fork_ids[0]]);
	pthread_mutex_unlock(&philo->forks[philo->fork_ids[1]]);
	print_message(philo->id, SLEEP, philo->config, philo->config->stop);
	ft_sleep(philo->config->sleep_time);
}

void	run_one_phil(t_phil *philo)
{
	pthread_mutex_lock(&philo->forks[philo->fork_ids[0]]);
	print_message(philo->id, FORK_TAKEN, philo->config, philo->config->stop);
	ft_sleep(philo->config->die_time);
}
