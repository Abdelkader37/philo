/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqrafi <aqrafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:12:36 by aqrafi            #+#    #+#             */
/*   Updated: 2025/08/01 16:21:28 by aqrafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*monitor_func(void *arg)
{
	t_philo	*philo;
	long	idx;

	philo = (t_philo *)arg;
	if (philo->arg->nphilo == 1)
		return (NULL);
	while (1)
	{
		idx = 0;
		while (idx < philo->arg->nphilo)
		{
			if (chek_meal(philo))
				return (NULL);
			if (!check_philo(&philo[idx]))
			{
				pthread_mutex_lock(&philo->arg->die);
				philo->arg->isalive = 0;
				pthread_mutex_unlock(&philo->arg->die);
				print_died(&philo[idx]);
				return (NULL);
			}
			idx++;
		}
		usleep(1);
	}
}

void	print_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print);
	printf("%lu %lu died\n", get_time() - philo->arg->start, philo->id);
	pthread_mutex_unlock(&philo->arg->print);
}

int	check_philo(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->meal);
	last_meal = philo->last_meal;
	if (get_time() - last_meal >= philo->arg->time_die)
	{
		pthread_mutex_unlock(&philo->meal);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->meal);
		return (1);
	}
}

int	chek_meal(t_philo *philo)
{
	int		flag;
	long	idx;

	if (!philo->arg->arg5)
		return (0);
	flag = 1;
	idx = 0;
	while (idx < philo->arg->nphilo)
	{
		pthread_mutex_lock(&philo[idx].meal);
		if (philo[idx].nmeals < philo[idx].arg->number_to_eat)
			flag = 0;
		pthread_mutex_unlock(&philo[idx].meal);
		idx++;
	}
	if (flag)
	{
		pthread_mutex_lock(&philo->arg->die);
		philo->arg->isalive = 0;
		pthread_mutex_unlock(&philo->arg->die);
	}
	return (flag);
}

int	check_life(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(&philo->arg->die);
	flag = philo->arg->isalive;
	pthread_mutex_unlock(&philo->arg->die);
	return (flag);
}
