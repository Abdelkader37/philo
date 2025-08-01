/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqrafi <aqrafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:08:33 by aqrafi            #+#    #+#             */
/*   Updated: 2025/07/31 19:49:17 by aqrafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_struct
{
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			meals;
	long			nphilo;
	long			start;
	long			number_to_eat;
	int				arg5;
	int				isalive;
	pthread_mutex_t	*fork;
	pthread_mutex_t	die;
	pthread_mutex_t	print;
}					t_arg;

typedef struct s_lst
{
	long			id;
	long			nmeals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal;
	t_arg			*arg;
}					t_philo;

// UTILS
long				ft_atoi(char *s);
t_arg				*init_arg(int ac, char **av);
void				print_died(t_philo *philo);
void				cleanup_resources(t_philo *philo, pthread_t monitor);

// THREAD FUNC
void				init_fork(t_arg *arg);
void				destroy_fork(t_arg *arg);
int					check_life(t_philo *philo);
void				*monitor_func(void *arg);
void				print(t_philo *philo, char *s);
int					check_life(t_philo *philo);
void				eat(t_philo *philo);
void				sleepp(t_philo *philo);
void				think(t_philo *philo);
void				create_threads(long nphilo, t_arg *arg);
void				*philo_fun(void *arg);
int					check_philo(t_philo *philo);
int					chek_meal(t_philo *philo);
void				one_philo(t_philo *philo);

// TIME
long				get_time(void);
void				ft_sleep(long target, t_philo *philo);

#endif