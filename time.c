#include "header.h"

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void	ft_sleep(unsigned long target, t_philo *philo)
{
	unsigned long start;

	start = get_time();
	while (get_time() - start < target && check_life(philo))
		usleep(100);
}