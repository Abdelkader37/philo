#include "header.h"

t_arg	*init_struct(int ac, char **av)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	arg->number_of_philosophers = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
    arg->isalive = 1;
	arg->allnmeal = 0;
	if (ac == 6)
		arg->number_of_times_to_eat = ft_atoi(av[5]);
	else if(ac == 5)
		arg->number_of_times_to_eat = 0;
	if (arg->number_of_philosophers <= 0 || arg->time_to_die <= 0
		|| arg->time_to_eat <= 0 || arg->time_to_sleep <= 0)
	{
		write(2, "Error: Invalid argument\n", 25);
		return (NULL);
	}
	else
		return (arg);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void	ft_sleep(unsigned long target, int flag)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < target && flag)
		usleep(100);
}
