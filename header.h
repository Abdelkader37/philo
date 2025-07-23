#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_list
{
	unsigned long	number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	number_of_times_to_eat;
	unsigned long	start_time;
    int             isalive;
	int				allnmeal;
	pthread_mutex_t	*fork;
	pthread_mutex_t	die;
	pthread_mutex_t	meal;

}					t_arg;

typedef struct s_lst
{
	unsigned long	id;
	unsigned long	nmeals;
	unsigned long	last_meal;
	pthread_t		thread;
	t_arg			*arg;
}					t_philo;

// thread_fun
void				creat_threads(unsigned long nfilo, t_arg *arg);
unsigned long		get_time(void);
void				ft_sleep(unsigned long target, int flag);
void				init_mtx(t_arg *arg);
int chek_life(int  is_alive, t_philo *philo);
void     chek_philo(t_philo *philo);
void     chek_meals(t_philo *philo);
void *monitor_func(void *arg);



// UTILS
unsigned long		ft_atoi(char *str);
t_arg				*init_struct(int ac, char **av);

#endif