/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqrafi <aqrafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:12:39 by aqrafi            #+#    #+#             */
/*   Updated: 2025/08/01 17:43:39 by aqrafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void	create_threads(long nphilo, t_arg *arg)
// {
// 	t_philo			*philo;
// 	pthread_t		monitor;
// 	long	idx;

// 	philo = malloc(sizeof(t_philo) * arg->nphilo);
// 	idx = 0;
// 	arg->start = get_time();
// 	while (idx < arg->nphilo)
// 	{
// 		philo[idx].id = idx + 1;
// 		philo[idx].nmeals = 0;
// 		philo[idx].last_meal = get_time();
// 		philo[idx].arg = arg;
// 		pthread_mutex_init(&philo[idx].meal, NULL);
// 		idx++;
// 	}
// 	pthread_create(&monitor, NULL, monitor_func, philo);
// 	idx = 0;
// 	while (idx < arg->nphilo)
// 	{
// 		pthread_create(&philo[idx].thread, NULL, philo_fun, &philo[idx]);
// 		idx++;
// 	}
// 	idx = 0;
// 	while (idx < nphilo)
// 	{
// 		pthread_join(philo[idx].thread, NULL);
// 		pthread_mutex_destroy(&philo[idx].meal);
// 		idx++;
// 	}
// 	pthread_detach(monitor);
// 	free(philo);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqrafi <aqrafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:12:39 by aqrafi            #+#    #+#             */
/*   Updated: 2025/07/31 17:19:42 by aqrafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_philo	*init_philosophers(t_arg *arg)
{
	t_philo	*philo;
	long	idx;

	philo = malloc(sizeof(t_philo) * arg->nphilo);
	if (!philo)
		return (NULL);
	idx = 0;
	arg->start = get_time();
	while (idx < arg->nphilo)
	{
		philo[idx].id = idx + 1;
		philo[idx].nmeals = 0;
		philo[idx].last_meal = get_time();
		philo[idx].arg = arg;
		pthread_mutex_init(&philo[idx].meal, NULL);
		idx++;
	}
	return (philo);
}

void	create_philosopher_threads(t_philo *philo, t_arg *arg)
{
	long	idx;

	idx = 0;
	while (idx < arg->nphilo)
	{
		pthread_create(&philo[idx].thread, NULL, philo_fun, &philo[idx]);
		idx++;
	}
}

void	join_philosopher_threads(t_philo *philo, long nphilo)
{
	long	idx;

	idx = 0;
	while (idx < nphilo)
	{
		pthread_join(philo[idx].thread, NULL);
		pthread_mutex_destroy(&philo[idx].meal);
		idx++;
	}
}

void	create_threads(long nphilo, t_arg *arg)
{
	t_philo		*philo;
	pthread_t	monitor;

	philo = init_philosophers(arg);
	if (!philo)
		return ;
	create_philosopher_threads(philo, arg);
	pthread_create(&monitor, NULL, monitor_func, philo);
	join_philosopher_threads(philo, nphilo);
	cleanup_resources(philo, monitor);
}

void	*philo_fun(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		think(philo);
		ft_sleep(philo->arg->time_eat, philo);
	}
	if (philo->arg->nphilo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (check_life(philo))
	{
		eat(philo);
		think(philo);
		sleepp(philo);
	}
	return (NULL);
}
