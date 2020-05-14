#include "philo_one.h"

extern int number_of_philosopher;
extern int time_to_die;
extern int time_to_eat;
extern int time_to_sleep;
extern int number_of_time_each_philosophers_must_eat;

void        ft_eat(s_philosof  *philo)
{
    struct timeval actual;

    if (philo->fork_left_id < philo->fork_right_id)
    {
        pthread_mutex_lock(philo->fork_left);
        printf("%ld : %d has taken his left fork\n", get_time_dif_l(philo->start) / 1000, philo->id);
        pthread_mutex_lock(philo->fork_right);
        printf("%ld : %d has taken his right fork\n", get_time_dif_l(philo->start) / 1000, philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->fork_right);
        printf("%ld : %d has taken his right fork\n", get_time_dif_l(philo->start) / 1000, philo->id);
        pthread_mutex_lock(philo->fork_left);
        printf("%ld : %d has taken his left fork\n", get_time_dif_l(philo->start) / 1000, philo->id);
    }
    printf("%ld : %d is eating\n", get_time_dif_l(philo->start) / 1000, philo->id);
    gettimeofday(&actual, NULL);
    philo->last_meal = get_time();
    usleep(time_to_eat * 1000);
    gettimeofday(&actual, NULL);
    philo->nb_meal += 1;
    philo->last_meal = get_time();
}

void        ft_sleep(s_philosof  *philo)
{
    printf("%ld : %d is sleeping\n", get_time_dif_l(philo->start) / 1000, philo->id);
    usleep(time_to_sleep * 1000);
}

void        ft_think(s_philosof  *philo)
{
    printf("%ld : %d is thinking\n", get_time_dif_l(philo->start) / 1000, philo->id);
}