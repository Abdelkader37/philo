#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_struct
{
    unsigned long   time_die;
    unsigned long   time_eat;
    unsigned long   time_sleep;
    unsigned long   meals;
    unsigned long   nphilo;
    unsigned long   start;
    unsigned long   number_to_eat;
    int             arg5;
    int             isalive;
    pthread_mutex_t	*fork;
	pthread_mutex_t	die;
	pthread_mutex_t	print;
}t_arg;

typedef struct s_lst
{
	unsigned long	id;
	unsigned long	nmeals;
	unsigned long	last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal;
	t_arg			*arg;
}					t_philo;

// UTILS
unsigned long   ft_atoi(char *s);
t_arg           *init_arg(int ac, char **av);


// THREAD FUNC
void            init_fork(t_arg *arg);
void            destroy_fork(t_arg *arg);
int             check_life(t_philo *philo);
void            *monitor_func(void *arg);
void            print(t_philo *philo, char *s);
int             check_life(t_philo *philo);
void            eat(t_philo *philo);
void            sleepp(t_philo *philo);
void            think(t_philo *philo);
void            create_threads(unsigned long nphilo, t_arg  *arg);
void            *philo_fun(void *arg);
int	            check_philo(t_philo philo);

// TIME
unsigned long	get_time(void);
void	        ft_sleep(unsigned long target, t_philo *philo);

#endif