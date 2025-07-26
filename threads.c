#include "header.h"

void eat(t_philo *philo)
{
    int left = philo->id - 1;
    int right = philo->id % philo->arg->number_of_philosophers;

    // Odd: take left first, Even: take right first
    if (philo->id % 2 == 1)
    {
        pthread_mutex_lock(&philo->arg->fork[left]);
        print(philo, "has taken a fork");        
        pthread_mutex_lock(&philo->arg->fork[right]);
        print(philo, "has taken a fork");        
    }
    else
    {
        pthread_mutex_lock(&philo->arg->fork[right]);
        print(philo, "has taken a fork");        
        pthread_mutex_lock(&philo->arg->fork[left]);
        print(philo, "has taken a fork");
    }

    pthread_mutex_lock(&philo->meal);
    philo->last_meal = get_time() - philo->arg->start_time;
    philo->nmeals++;
    pthread_mutex_unlock(&philo->meal);
    print(philo, "is eating");
    ft_sleep(philo->arg->time_to_eat, philo);

    pthread_mutex_unlock(&philo->arg->fork[left]);
    pthread_mutex_unlock(&philo->arg->fork[right]);
}

 void think(t_philo *philo)
{
    if(chek_life(philo))
        print(philo, "is thinking");
}
void sleeep(t_philo *philo)
{
    if(chek_life(philo))
        print(philo, "is sleeping");        
    ft_sleep(philo->arg->time_to_sleep, philo);
}
void *filo_function(void *argm)
{
    t_philo *philo;

    philo = (t_philo *)argm;
    if(philo->id % 2 == 0)
        usleep(400);
    while (chek_life(philo))
    {
        if (chek_life(philo))
            think(philo);
        if(chek_life(philo))
            eat(philo);
        if (!chek_life(philo))
            break;
        if (chek_life(philo))
            sleeep(philo);
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
        pthread_mutex_init(&philo[idx].meal, NULL);
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
    pthread_join(monitor, NULL);
    free(arg);
}

void init_mtx(t_arg *arg)
{
    unsigned long  idx;

    arg->fork = malloc(sizeof(pthread_mutex_t ) * arg->number_of_philosophers);
    pthread_mutex_init(&arg->die, NULL);
    pthread_mutex_init(&arg->print, NULL);
    idx = 0;
    while (idx < arg->number_of_philosophers)
    {
        pthread_mutex_init(&arg->fork[idx], NULL);
        idx++;
    }
}

int chek_life(t_philo *philo)
{
    int flag;

    flag = 0;
    pthread_mutex_lock(&philo->arg->die);
    if (philo->arg->isalive)
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }
    pthread_mutex_unlock(&philo->arg->die);
    return(flag);
}

void *monitor_func(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (chek_life(philo))
    {
        chek_philo(philo);
        // if(philo->arg->number_of_times_to_eat == 0)
        //     chek_meals(philo);
    }
    return(NULL);
}
void     chek_meals(t_philo *philo)
{
    unsigned long idx;
    int flag;

    flag = 0;
    while (chek_life(philo))
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

    while (chek_life(philo))
    {
        idx = 0;
        while (idx < philo->arg->number_of_philosophers)
        {
            if (chek_last_meal(philo[idx]))
           { 
            pthread_mutex_lock(&philo->arg->die);
                philo[idx].arg->isalive = 0;
            pthread_mutex_unlock(&philo->arg->die);
            }
            if(!chek_life(philo))
                break;
            idx++;
        }
    }
    usleep(100);
    if(!chek_life(philo))
    {
        pthread_mutex_lock(&philo->arg->print);
        printf("%lu %lu is died\n", get_time() -  philo->arg->start_time, philo->id);        
        pthread_mutex_unlock(&philo->arg->print);
    }
}


int chek_last_meal(t_philo philo)
{
    int             flag;
    unsigned long   last_meal;

    pthread_mutex_lock(&philo.meal);
    last_meal = philo.last_meal;
    pthread_mutex_unlock(&philo.meal);
    if(get_time() - philo.arg->start_time - last_meal > philo.arg->time_to_die)
        flag = 1;
    else
        flag = 0;
    return(flag);
}
void print(t_philo *philo, char *s)
{
    if(chek_life(philo))
    {
        pthread_mutex_lock(&philo->arg->print);
        printf("%lu %lu  %s\n", get_time() - philo->arg->start_time, philo->id, s);
        pthread_mutex_unlock(&philo->arg->print);
    }
}