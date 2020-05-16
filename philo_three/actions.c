#include "philo_one.h"

extern int time_to_eat;
extern int time_to_sleep;
extern int end;

void        ft_eat(s_philosof  *philo)
{

    sem_wait(philo->fork);
    put_message(philo, " take his first fork\n");
    put_message(philo, " take his second fork\n");

    put_message(philo, " is eating\n");
    philo->last_meal = get_time();
    usleep(time_to_eat * 1000);
    philo->nb_meal += 1;
    philo->last_meal = get_time();
    sem_post(philo->fork);
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