#include "header.h"

t_arg	*init_arg(int ac, char **av)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg ));
	arg->nphilo = ft_atoi(av[1]);
	arg->time_die = ft_atoi(av[2]);
	arg->time_eat = ft_atoi(av[3]);
	arg->time_sleep = ft_atoi(av[4]);
	if (ac == 5)
		arg->arg5 = 0;
	else
	{
		arg->arg5 = 1;
		arg->number_to_eat = ft_atoi(av[5]);
	}
	if (!arg->time_die || !arg->time_eat || !arg->time_sleep || !arg->nphilo)
	{
		write(2, "Error: Invalid argument\n", 25);
		return (NULL);
	}
	arg->isalive = 1;
	arg->meals = 0;
	pthread_mutex_init(&arg->die, NULL);
	pthread_mutex_init(&arg->print, NULL);
	return (arg);
}

void	init_fork(t_arg *arg)
{
	unsigned long	i;

	i = 0;
	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->nphilo);
	while (i < arg->nphilo)
	{
		pthread_mutex_init(&arg->fork[i], NULL);
		i++;
	}
}
void	destroy_fork(t_arg *arg)
{
	unsigned long	i;

	i = 0;
	while (i < arg->nphilo)
	{
		pthread_mutex_destroy(&arg->fork[i]);
		i++;
	}
	free(arg->fork);
}

void	print(t_philo *philo, char *s)
{
    pthread_mutex_lock(&philo->arg->print);
	if (check_life(philo))
		printf("%lu %lu %s\n", get_time() - philo->arg->start, philo->id, s);
    pthread_mutex_unlock(&philo->arg->print);
}
