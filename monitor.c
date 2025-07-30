
#include "header.h"

// void	*monitor_func(void *arg)
// {
//     t_philo *philo;
//     unsigned long idx;
//     int flag;

//     philo = (t_philo *)arg;
//     while (1)
//     {
//         print(philo, "***\n");
//         idx = 0;
//         flag = 1;
//         while (idx < philo->arg->nphilo)
//         {
//             if(!check_philo(philo[idx]))
//             {
//                 pthread_mutex_lock(&philo->arg->print);
//                 pthread_mutex_lock(&philo->arg->die);
//                 philo->arg->isalive = 0;
//                 pthread_mutex_unlock(&philo->arg->die);
//                 printf("%lu %lu died\n", get_time() - philo->arg->start, philo[idx].id);
//                 pthread_mutex_unlock(&philo->arg->print);
//                 return(NULL);
//             }
//             idx++;
//         }
//         usleep(400);
//     }
// }

// int	check_philo(t_philo philo)
// {
// 	unsigned long	last_meal;
//     // unsigned long   time;

// 	pthread_mutex_lock(&philo.meal);
// 	last_meal = philo.last_meal;
// 	if (get_time() - last_meal >= philo.arg->time_die)
//     {
// 	    pthread_mutex_unlock(&philo.meal);
// 		return(0);
//     }
// 	else
//     {
// 	    pthread_mutex_unlock(&philo.meal);
//         return(1);
//     }
// }
// void *monitor_func(void *arg)
// {
//     t_philo *philo;
//     unsigned long idx;
//     int flag;
    
//     philo = (t_philo *)arg;
//     while (1)
//     {
//         print(philo, "***\n");
//         idx = 0;
//         flag = 1;
//         while (idx < philo->arg->nphilo)
//         {
//             // Inline check_philo logic
//             pthread_mutex_lock(&philo[idx].meal);
//             if (get_time() - philo[idx].last_meal >= philo->arg->time_die)
//             {
//                 pthread_mutex_unlock(&philo[idx].meal);
//                 // Philosopher has died
//                 pthread_mutex_lock(&philo->arg->print);
//                 pthread_mutex_lock(&philo->arg->die);
//                 philo->arg->isalive = 0;
//                 pthread_mutex_unlock(&philo->arg->die);
//                 printf("%lu %lu died\n", get_time() - philo->arg->start, philo[idx].id);
//                 pthread_mutex_unlock(&philo->arg->print);
//                 return(NULL);
//             }
//             else
//             {
//                 pthread_mutex_unlock(&philo[idx].meal);
//             }
//             idx++;
//         }
//         usleep(400);
//     }
// }
void *monitor_func(void *arg)
{
    t_philo *philo;
    unsigned long idx;
    int flag;
    unsigned long last_meal;
    
    philo = (t_philo *)arg;
    while (1)
    {
        // print(philo, "***\n");
        idx = 0;
        flag = 1;
        while (idx < philo->arg->nphilo)
        {
            // Inline check_philo logic
            pthread_mutex_lock(&philo[idx].meal);
            last_meal = philo[idx].last_meal;
            if (get_time() - last_meal >= philo->arg->time_die)
            {
                // Philosopher has died
                pthread_mutex_unlock(&philo[idx].meal);
                pthread_mutex_lock(&philo->arg->print);
                pthread_mutex_lock(&philo->arg->die);
                philo->arg->isalive = 0;
                pthread_mutex_unlock(&philo->arg->die);
                printf("%lu %lu died\n", get_time() - philo->arg->start, philo[idx].id);
                pthread_mutex_unlock(&philo->arg->print);
                return(NULL);
            }
            pthread_mutex_unlock(&philo[idx].meal);
            idx++;
        }
        usleep(1);
    }
}