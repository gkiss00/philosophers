#include "philo_one.h"

extern int time_to_eat;
extern int time_to_sleep;
extern int end;

void        ft_eat(s_philosof  *philo)
{
    if (philo->fork_left_id < philo->fork_right_id)
    {
        pthread_mutex_lock(philo->fork_left);
        put_message(philo, " taken his left fork\n");
        pthread_mutex_lock(philo->fork_right);
        put_message(philo, " taken his right fork\n");
    }
    else
    {
        pthread_mutex_lock(philo->fork_right);
        put_message(philo, " taken his right fork\n");
        pthread_mutex_lock(philo->fork_left);
        put_message(philo, " taken his left fork\n");
    }
    put_message(philo, " is eating\n");
    philo->last_meal = get_time();
    usleep(time_to_eat * 1000);
    philo->nb_meal += 1;
    philo->last_meal = get_time();
}

void        ft_sleep(s_philosof  *philo)
{
    if (*philo->alive == 1 && end == 0)
    {
        put_message(philo, " is sleeping\n");
        usleep(time_to_sleep * 1000);
    }
}

void        ft_think(s_philosof  *philo)
{
    if (*philo->alive == 1 && end == 0)
        put_message(philo, " is thinking\n");
}