#include "philo_one.h"

extern int number_of_philosopher;
extern int time_to_die;
extern int time_to_eat;
extern int time_to_sleep;
extern int number_of_time_each_philosophers_must_eat;

void        ft_sleep(struct timeval start, s_philosof  *philo)
{
    printf("%ld : %d is sleeping\n", get_time_dif(start), philo->id);
    usleep(time_to_sleep * 1000);
}

void        ft_eat(struct timeval start, s_philosof  *philo)
{
    if (philo->fork_left_id < philo->fork_right_id)
    {
        pthread_mutex_lock(philo->fork_left);
        printf("%ld : %d has taken his left fork %d\n", get_time_dif(start), philo->id, philo->fork_left_id);
        pthread_mutex_lock(philo->fork_right);
        printf("%ld : %d has taken his right fork %d\n", get_time_dif(start), philo->id, philo->fork_right_id);
    }
    else
    {
        pthread_mutex_lock(philo->fork_right);
        printf("%ld : %d has taken his right fork %d\n", get_time_dif(start), philo->id, philo->fork_right_id);
        pthread_mutex_lock(philo->fork_left);
        printf("%ld : %d has taken his left fork %d\n", get_time_dif(start), philo->id, philo->fork_left_id);
    }
    printf("%ld : %d is eating\n", get_time_dif(start), philo->id);
    usleep(time_to_eat * 1000);
}

void        ft_think(struct timeval start, s_philosof  *philo)
{
    printf("%ld : %d is thinking\n", get_time_dif(start), philo->id);
}