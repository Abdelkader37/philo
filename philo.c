/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqrafi <aqrafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:11:50 by aqrafi            #+#    #+#             */
/*   Updated: 2025/07/31 19:21:16 by aqrafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->fork[0]);
	print(philo, "has taken a fork");
	ft_sleep(philo->arg->time_die, philo);
	pthread_mutex_unlock(&philo->arg->fork[0]);
	print(philo, "died");
}
