#include "philo_one.h"

extern int number_of_philosopher;
extern int time_to_die;
extern int time_to_eat;
extern int time_to_sleep;
extern int number_of_time_each_philosophers_must_eat;

void        ft_sleep(struct timeval start, s_philosof  *philo)
{
    printf("%ld : %d is sleeping\n", get_time_dif(start) / 1000, philo->id);
    usleep(time_to_sleep * 1000);
}

long int        ft_eat(struct timeval start, s_philosof  *philo)
{
    if (philo->fork_left_id < philo->fork_right_id)
    {
        printf("%d\n", pthread_mutex_lock(philo->fork_left));
        printf("%ld : %d has taken his left fork\n", get_time_dif(start) / 1000, philo->id);
        pthread_mutex_lock(philo->fork_right);
        printf("%ld : %d has taken his right fork\n", get_time_dif(start) / 1000, philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->fork_right);
        printf("%ld : %d has taken his right fork\n", get_time_dif(start) / 1000, philo->id);
        pthread_mutex_lock(philo->fork_left);
        printf("%ld : %d has taken his left fork\n", get_time_dif(start) / 1000, philo->id);
    }
    printf("%ld : %d is eating\n", get_time_dif(start) / 1000, philo->id);
    usleep(time_to_eat * 1000);
    philo->nb_meal += 1;
    return (get_time_dif(start));
}

void        ft_think(struct timeval start, s_philosof  *philo)
{
    printf("%ld : %d is thinking\n", get_time_dif(start) / 1000, philo->id);
}