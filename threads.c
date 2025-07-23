#include "header.h"

void eat(t_philo *philo)
{
    if(!chek_life(philo->arg->isalive, philo))
        return;
    if(philo->id == philo->arg->number_of_philosophers)
        pthread_mutex_lock(&philo->arg->fork[0]);
    else
        pthread_mutex_lock(&philo->arg->fork[(philo->id)]);
    if(chek_life(philo->arg->isalive, philo))
        printf("%lu %lu  has taken a fork\n",get_time() - philo->arg->start_time, philo->id);
    if(!chek_life(philo->arg->isalive, philo))
        return;
    pthread_mutex_lock(&philo->arg->fork[philo->id  - 1]);
    if(chek_life(philo->arg->isalive, philo))
        printf("%lu %lu  has taken a fork\n", get_time() - philo->arg->start_time, philo->id);
    philo->last_meal = get_time() - philo->arg->start_time;
    if(!chek_life(philo->arg->isalive, philo))
        return;
    printf("%lu %lu  is eating\n", get_time() - philo->arg->start_time, philo->id);
    ft_sleep(philo->arg->time_to_eat, philo->arg->isalive);
    if(philo->id == philo->arg->number_of_philosophers)
        pthread_mutex_unlock(&philo->arg->fork[0]);
    else
    pthread_mutex_unlock(&philo->arg->fork[(philo->id)]);
    pthread_mutex_unlock(&philo->arg->fork[philo->id  - 1]);
    philo->nmeals++;
}
 void think(t_philo *philo)
{
    if(chek_life(philo->arg->isalive, philo))
        printf("%lu %lu  is thinking\n", get_time() - philo->arg->start_time, philo->id);
}
void sleeep(t_philo *philo)
{
    if(chek_life(philo->arg->isalive, philo))
        printf("%lu %lu  is sleeping\n", get_time() - philo->arg->start_time, philo->id);
    ft_sleep(philo->arg->time_to_sleep, philo->arg->isalive);
}
void *filo_function(void *argm)
{
    t_philo *philo; 
    int flag;

    flag = 1;
    philo = (t_philo *)argm;
    if(philo->id % 2 == 0)
        flag = 0;
    while (philo->arg->isalive)
    {
        if(flag && chek_life(philo->arg->isalive, philo))
            eat(philo);
        if (!chek_life(philo->arg->isalive, philo))
            break;
        flag = 1;
        if (chek_life(philo->arg->isalive, philo))
            sleeep(philo);
        if (chek_life(philo->arg->isalive, philo))
            think(philo);
    }
    return(NULL);
}
void creat_threads(unsigned long nfilo, t_arg *arg)
{
    t_philo philo[nfilo];
    pthread_t   monitor;
    unsigned long idx;

    idx = 0;
    arg->start_time = get_time();
    init_mtx(arg);
    while (idx < nfilo)
    {
        philo[idx].id = idx + 1;
        philo[idx].arg = arg;
        philo[idx].last_meal = 0;
        pthread_create(&philo[idx].thread, NULL, filo_function, &philo[idx]);
        idx++;
    }
    pthread_create(&monitor, NULL, monitor_func, philo);
    idx = 0;
    while (idx < nfilo)
    {
        pthread_join(philo[idx].thread, NULL);
        idx++;
    }
    free(arg);
}

void init_mtx(t_arg *arg)
{
    unsigned long  idx;

    arg->fork = malloc(sizeof(pthread_mutex_t ) * arg->number_of_philosophers);
    pthread_mutex_init(&arg->die, NULL);
    idx = 0;
    while (idx < arg->number_of_philosophers)
    {
        pthread_mutex_init(&arg->fork[idx], NULL);
        idx++;
    }
}

int chek_life(int  is_alive, t_philo *philo)
{
    int flag;

    flag = 0;
    pthread_mutex_lock(&philo->arg->die);
    if (is_alive)
        flag = 1;
    else if (is_alive == 0)
        flag = 0;
    pthread_mutex_unlock(&philo->arg->die);
    return(flag);
}

void *monitor_func(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (philo->arg->isalive)
    {
        chek_philo(philo);
        if(philo->arg->number_of_times_to_eat == 0)
            chek_meals(philo);
    }
    return(NULL);
}
void     chek_meals(t_philo *philo)
{
    unsigned long idx;
    int flag;

    flag = 0;
    while (philo->arg->isalive)
    {
        idx = 0;
        while (idx < philo->arg->number_of_philosophers || !flag)
        {
            if(philo[idx].nmeals < philo->arg->number_of_times_to_eat)
                flag = 0;
            idx++;
        }
        if (flag)
        {
            pthread_mutex_lock(&philo->arg->die);
            philo->arg->isalive = 0;
            pthread_mutex_unlock(&philo->arg->die);
            return;
        }
        flag = 1;
    }
    
}
void     chek_philo(t_philo *philo)
{
    unsigned long idx;

    while (philo->arg->isalive)
    {
        idx = 0;
        while (idx < philo->arg->number_of_philosophers)
        {
            pthread_mutex_lock(&philo->arg->die);
            if (get_time() - philo[idx].arg->start_time - philo[idx].last_meal > philo[idx].arg->time_to_die)
            {
                philo[idx].arg->isalive = 0;
            }
            pthread_mutex_unlock(&philo->arg->die);
            if(!philo[idx].arg->isalive)
                break;
            idx++;
        }
    }
    usleep(100);
    printf("%lu %lu  died\n", get_time() - philo[idx].arg->start_time, philo[idx].id);
}
