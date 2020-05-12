#include "philo_one.h"

extern int number_of_philosopher;
extern int time_to_die;
extern int time_to_eat;
extern int time_to_sleep;
extern int number_of_time_each_philosophers_must_eat;

void *start(void *arg)
{
    s_philosof  *philo;
    int         fork_left;
    int         fork_right;
    useconds_t t = time_to_sleep * 1000;
    struct timeval actual;
    struct timeval start;

    gettimeofday(&start, NULL);
    philo = (s_philosof*)arg;
    fork_left = philo->id - 1;
    fork_right = philo->id % number_of_philosopher;
    while(1)
    {
        if (fork_left < fork_right)
        {
            pthread_mutex_lock(philo->fork_left);
            gettimeofday(&actual, NULL);
            printf("%ld : %d has taken his left fork %d\n",((actual.tv_sec * 1000000) +  actual.tv_usec) - ((start.tv_sec * 1000000) +  start.tv_usec), philo->id - 1, fork_left);
            pthread_mutex_lock(philo->fork_right);
            gettimeofday(&actual, NULL);
            printf("%ld : %d has taken his right fork %d\n", ((actual.tv_sec * 1000000) +  actual.tv_usec) - ((start.tv_sec * 1000000) +  start.tv_usec), philo->id - 1, fork_right);
        }
        else
        {
            pthread_mutex_lock(philo->fork_right);
            gettimeofday(&actual, NULL);
            printf("%ld : %d has taken his right fork %d\n", ((actual.tv_sec * 1000000) +  actual.tv_usec) - ((start.tv_sec * 1000000) +  start.tv_usec), philo->id - 1, fork_right);
            pthread_mutex_lock(philo->fork_left);
            gettimeofday(&actual, NULL);
            printf("%ld : %d has taken his left fork %d\n", ((actual.tv_sec * 1000000) +  actual.tv_usec) - ((start.tv_sec * 1000000) +  start.tv_usec), philo->id - 1, fork_left);
        }
        usleep(t);
        printf("je suis le thread %d\n", philo->id - 1);
        pthread_mutex_unlock(philo->fork_left);
        gettimeofday(&actual, NULL);
        printf("%ld : %d puts down his left fork %d\n", ((actual.tv_sec * 1000000) +  actual.tv_usec) - ((start.tv_sec * 1000000) +  start.tv_usec), philo->id - 1, fork_left);
        pthread_mutex_unlock(philo->fork_right);
        gettimeofday(&actual, NULL);
        printf("%ld : %d puts down his right fork %d\n", ((actual.tv_sec * 1000000) +  actual.tv_usec) - ((start.tv_sec * 1000000) +  start.tv_usec), philo->id - 1, fork_right);
        
        
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