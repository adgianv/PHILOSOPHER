#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

unsigned long long	now_ts(void)
{
	struct timeval	current_time;
	unsigned long long		t;

	gettimeofday(&current_time, (void *)0);
	t = (current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000;
	return (t);
}

void	start_wait(unsigned long long st)
{
	while (now_ts() < st)
		continue ;
}

int	parser(t_conf *config, int argc, char *argv[])
{
	int	i;
	int	c;

	i = 0;
	while (++i < argc)
	{
		c = -1;
		while (argv[i][++c])
			if (!is_digit(argv[i][c]))
				return (1);
	}
	populate_config(config, argv, argc);
	pthread_mutex_init(&config->lock_print, NULL);
	// pthread_mutex_init(&config->lock_print, (void *)0);
	return (0);
}

void	ft_sleep(int ms)
{
	unsigned long long	f;

	f = now_ts() + ms;
	while (now_ts() < f)
		usleep(100);
}
