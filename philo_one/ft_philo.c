#include "philo_one.h"

pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *hello(void *arg)
{
    int     i;
    struct timeval  start;

    i = 0;
    while (i < 10)
    {
        gettimeofday(&start, NULL);
        printf("%ld %d\n", start.tv_sec, start.tv_usec);
        puts((char*)arg);
        ++i;
    }
    pthread_exit(arg);
}

static void ft_init_data(int lenght, s_philosof tab[], int fork[])
{
    int     i;

    i = 0;
    while (i < lenght)
    {
        tab[i].id = 1;
        tab[i].alive = 1;
        fork[i] = 1;
        ++i;
    }
}

void    begin_experiment(s_data *data)
{
    s_philosof      philosopher[data->number_of_philosopher];
    int             fork[data->number_of_philosopher];
    pthread_t       thread[data->number_of_philosopher];

    ft_init_data(data->number_of_philosopher, philosopher, fork);
    if(pthread_create(&thread[0], NULL, hello, "oui") == -1)
        puts("error");
    pthread_join(thread[0], NULL);
}