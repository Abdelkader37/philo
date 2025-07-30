#include "header.h"

void	create_threads(unsigned long nphilo, t_arg *arg)
{
	t_philo			*philo;
	pthread_t		monitor;
	unsigned long	idx;

	philo = malloc(sizeof(t_philo) * arg->nphilo);
	idx = 0;
	arg->start = get_time();
	while (idx < arg->nphilo)
	{
		philo[idx].id = idx + 1;
		philo[idx].last_meal = arg->start;
		philo[idx].nmeals = 0;
		philo[idx].arg = arg;
		pthread_mutex_init(&philo[idx].meal, NULL);
		idx++;
	}
	pthread_create(&monitor, NULL, monitor_func, philo);
	idx = 0;
	while (idx < arg->nphilo)
	{	pthread_create(&philo[idx].thread, NULL, philo_fun, &philo[idx]);
		idx++;
	}
	idx = 0;
	while (idx < nphilo)
	{
		pthread_join(philo[idx].thread, NULL);
		pthread_mutex_destroy(&philo[idx].meal);
		idx++;
	}
    pthread_detach(monitor);
	free(philo);
}

void	*philo_fun(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);
	while (check_life(philo))
	{
		think(philo);
		eat(philo);
		sleepp(philo);
	}
	return (NULL);
}

int	check_life(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(&philo->arg->die);
	flag = philo->arg->isalive;
	pthread_mutex_unlock(&philo->arg->die);
	return (flag);
}
void	eat(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->arg->nphilo;
	pthread_mutex_lock(&philo->arg->fork[left]);
	print(philo, "has taken a fork");        
	pthread_mutex_lock(&philo->arg->fork[right]);
	print(philo, "has taken a fork");
	if (!check_life(philo))
	{
		pthread_mutex_unlock(&philo->arg->fork[philo->id % philo->arg->nphilo]);
		pthread_mutex_unlock(&philo->arg->fork[philo->id - 1]);
		return ;
	}
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_time();
	philo->nmeals++;
	pthread_mutex_unlock(&philo->meal);
	print(philo, "is eating");
	ft_sleep(philo->arg->time_eat, philo);
	pthread_mutex_unlock(&philo->arg->fork[philo->id % philo->arg->nphilo]);
	pthread_mutex_unlock(&philo->arg->fork[philo->id - 1]);
}

void	sleepp(t_philo *philo)
{
	print(philo, "is sleeping");
	ft_sleep(philo->arg->time_sleep, philo);
}
void	think(t_philo *philo)
{
	print(philo, "is thinking");
}