#include "philo_one.h"

extern int number_of_philosopher;
extern int time_to_die;
extern int time_to_eat;
extern int time_to_sleep;
extern int number_of_time_each_philosophers_must_eat;

void *start(void *arg)
{
    s_philosof  *philo;
    struct timeval start;

    gettimeofday(&start, NULL);
    philo = (s_philosof*)arg;
    while(1)
    {
        ft_eat(start, philo);
        pthread_mutex_unlock(philo->fork_left);
        printf("%ld : %d puts down his left fork %d\n", get_time_dif(start), philo->id, philo->fork_left_id);
        pthread_mutex_unlock(philo->fork_right);
        printf("%ld : %d puts down his right fork %d\n", get_time_dif(start), philo->id, philo->fork_right_id);
        ft_sleep(start, philo);
        ft_think(start, philo);
    }
    return (NULL);
}

void init_phil(s_philosof philo[number_of_philosopher], pthread_mutex_t fork[number_of_philosopher])
{
    int i;

    i = 0;
    while (i < number_of_philosopher)
    {
        philo[i].id = i + 1;
        philo[i].alive = 1;
        philo[i].fork_left_id = i;
        philo[i].fork_right_id = (i + 1) % number_of_philosopher;
        philo[i].fork_left = &fork[i];
        philo[i].fork_right = &fork[(i + 1) % number_of_philosopher];
        ++i;
    }
}

void begin_simulation()
{
    int             i;
    s_philosof      philo[number_of_philosopher];
    pthread_t       phil[number_of_philosopher];
    pthread_mutex_t fork[number_of_philosopher];
    

    i = -1;
    while (++i < number_of_philosopher)
        pthread_mutex_init(&fork[i], NULL);

    i = -1;
    while (++i < number_of_philosopher)
        init_phil(philo, fork);
    i = -1;
    while (++i < number_of_philosopher)
        pthread_create(&phil[i], NULL, start, (void*)&philo[i]);
    
    
    pthread_join(phil[0], NULL);
}