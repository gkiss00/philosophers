#include "philo_one.h"

extern int  n_p;
extern int  time_to_die;
extern int  time_to_eat;
extern int  time_to_sleep;
extern int  me;
int         alive = 1;
int         end = 0;

static void    end_simulation(s_philosof philo[n_p], int nb, int i)
{
    while(*philo[0].alive == 1 && end == 0)
    {
        if (me >= 0)
        {
            nb = 0;
            i = 0;
            while (i < n_p)
            {
                if (philo[i].nb_meal >= me)
                    ++nb;
                ++i;
            }
            if (nb == n_p)
            {
                sem_wait(philo->write);
                ft_putstr("Tout les philosophes ont mangé ");
                ft_putnbr(me);
                ft_putstr(" fois. La simulation prend fin.\n");
                end = 1;
                sem_post(philo->write);
            }    
        }
    }
}

static void     *death_controle(void *arg)
{
    s_philosof      *philo;

    philo = (s_philosof*)arg;
    while(*philo->alive == 1 && end == 0 && me != 0)
    {
        if (get_time_dif_l(philo->last_meal) / 1000 > time_to_die)
        {
            put_message_end(philo, " just died\n");
            *philo->alive = 0;
        }
    }
    return (NULL);
}

static void     *start(void *arg)
{
    s_philosof      *philo;

    philo = (s_philosof*)arg;
    if (philo->id % 2 == 0)
        usleep((time_to_eat + time_to_sleep) * 1000 / 2);
    while(*philo->alive == 1 && end == 0 && me != 0)
    {
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
        if (alive == 1 && end == 0 && time_to_sleep == 0)
            usleep(time_to_eat * 1000 / 2);
        
    }
    return (NULL);
}

static void    init_phil(s_philosof philo[n_p])
{
    int             i;
    long int        start;
    sem_t           *fork[2];

    i = 0;
    start = get_time();
    fork[0] = sem_open("fork", O_CREAT, 0600, n_p / 2);
    fork[1] = sem_open("write", O_CREAT, 0600, 1);
    while (i < n_p)
    {
        philo[i].id = i + 1;
        philo[i].alive = &alive;
        philo[i].nb_meal = 0;
        philo[i].last_meal = start;
        philo[i].fork = fork[0];
        philo[i].write = fork[1];
        philo[i].start = start;
        ++i;
    }
}

void            begin_simulation()
{
    int             i;
    s_philosof      philo[n_p];
    pthread_t       phil[n_p];
    pthread_t       death[n_p];
    
    sem_unlink("fork");
    sem_unlink("write");
    init_phil(philo);
    i = -1;
    while (++i < n_p)
    {
        pthread_create(&phil[i], NULL, start, (void*)&philo[i]);
        pthread_create(&death[i], NULL, death_controle, (void*)&philo[i]);
    }
    end_simulation(philo, 0, 0);
    i = -1;
    while (++i < n_p)
    pthread_join(phil[i], NULL);
    sem_unlink("fork");
    sem_unlink("write");
}