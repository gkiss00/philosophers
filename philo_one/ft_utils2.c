#include "philo_one.h"

long int    get_time()
{
    long int act;
    struct timeval actual;

    gettimeofday(&actual, NULL);
    act = ((actual.tv_sec * 1000000) +  actual.tv_usec);
    return (act);
}

long int    get_time_dif_l(long int start)
{
    long int dif;
    struct timeval actual;

    gettimeofday(&actual, NULL);
    dif = ((actual.tv_sec * 1000000) +  actual.tv_usec);
    dif -= start;
    return (dif);
}

long int    get_time_dif_ll(long int start, long int actual)
{
    long int dif;

    dif = actual;
    dif -= start;
    return (dif);
}

long int    get_time_dif(struct timeval start)
{
    long int dif;
    struct timeval actual;

    gettimeofday(&actual, NULL);
    dif = ((actual.tv_sec * 1000000) +  actual.tv_usec);
    dif -= ((start.tv_sec * 1000000) +  start.tv_usec);
    return (dif);
}

void        put_message(s_philosof *philo, char *msg)
{
    pthread_mutex_lock(philo->write);
    ft_putnbr(get_time_dif_l(philo->start) / 1000);
    ft_putstr(" : ");
    ft_putnbr(philo->id);
    ft_putstr(msg);
    pthread_mutex_unlock(philo->write);
}