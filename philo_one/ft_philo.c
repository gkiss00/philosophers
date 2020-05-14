#include "philo_one.h"

extern int  number_of_philosopher;
extern int  time_to_die;
extern int  time_to_eat;
extern int  time_to_sleep;
extern int  number_of_time_each_philosophers_must_eat;
int         alive = 1;

static void    end_simulation(s_philosof philo[number_of_philosopher])
{
    int     nb;
    int     i;

    while(*philo[0].alive == 1)
    {
        if (number_of_time_each_philosophers_must_eat > 0)
        {
            nb = 0;
            i = 0;
            while (i < number_of_philosopher)
            {
                if (philo[i].nb_meal >= number_of_time_each_philosophers_must_eat)
                    ++nb;
                ++i;
            }
            if (nb == number_of_philosopher)
                return;
        }
    }
}

static void     *death_controle(void *arg)
{
    s_philosof      *philo;

    philo = (s_philosof*)arg;
    while(*philo->alive == 1)
    {
        if (get_time_dif_l(philo->last_meal) > time_to_die * 1000)
        {
            printf("%ld : %d just died\n", get_time_dif_l(philo->start) / 1000, philo->id);
            *philo->alive = 0;
        }
    }
    return (NULL);
}

static void     *start(void *arg)
{
    s_philosof      *philo;

    philo = (s_philosof*)arg;
    while(*philo->alive == 1)
    {
        ft_eat(philo);
        printf("%ld : %d puts down his left fork\n", get_time_dif_l(philo->start) / 1000, philo->id);
        pthread_mutex_unlock(philo->fork_left);
        printf("%ld : %d puts down his right fork\n", get_time_dif_l(philo->start) / 1000, philo->id);
        pthread_mutex_unlock(philo->fork_right);
        ft_sleep(philo);
        ft_think(philo);
    }
    return (NULL);
}

static void    init_phil(s_philosof philo[number_of_philosopher], pthread_mutex_t fork[number_of_philosopher])
{
    int             i;
    long int        start;

    i = 0;
    start = get_time();
    while (i < number_of_philosopher)
    {
        philo[i].id = i + 1;
        philo[i].alive = &alive;
        philo[i].nb_meal = 0;
        philo[i].last_meal = start;
        philo[i].fork_left_id = i;
        philo[i].fork_right_id = (i + 1) % number_of_philosopher;
        philo[i].fork_left = &fork[i];
        philo[i].fork_right = &fork[(i + 1) % number_of_philosopher];
        philo[i].start = start;
        ++i;
    }
}

void            begin_simulation()
{
    int             i;
    s_philosof      philo[number_of_philosopher];
    pthread_t       phil[number_of_philosopher];
    pthread_t       death[number_of_philosopher];
    pthread_mutex_t fork[number_of_philosopher];

    i = -1;
    while (++i < number_of_philosopher)
        pthread_mutex_init(&fork[i], NULL);
    init_phil(philo, fork);
    i = -1;
    while (++i < number_of_philosopher)
    {
        pthread_create(&phil[i], NULL, start, (void*)&philo[i]);
        pthread_create(&death[i], NULL, death_controle, (void*)&philo[i]);
    }
    end_simulation(philo);
}