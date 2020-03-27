#include "philo_one.h"

pthread_mutex_t mutex;

static void *hello(void *arg)
{
    s_philosof *p;
    int     i;
    struct timeval  start;
    struct timeval  actual;

    i = 0;
    p = (s_philosof*)arg;
    gettimeofday(&start, NULL);
    while (i < 10)
    {
        gettimeofday(&actual, NULL);
        printf("etape : %d temps ecoule : %ld secondes et %d microsecondes ::: philosopher %d is alive ? %d\n", i, actual.tv_sec - start.tv_sec, actual.tv_usec - start.tv_usec, p->id, p->alive);
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
        tab[i].id = i + 1;
        tab[i].alive = 1;
        fork[i] = 1;
        ++i;
    }
}

void    begin_experiment(s_data *data)
{
    int             i;
    s_philosof      philosopher[data->number_of_philosopher];
    int             fork[data->number_of_philosopher];
    pthread_t       thread[data->number_of_philosopher];

    i = 0;
    ft_init_data(data->number_of_philosopher, philosopher, fork);
    while (i < data->number_of_philosopher)
    {
        if(pthread_create(&thread[i], NULL, hello, &philosopher[i]) == -1)
            puts("error");
        ++i;
    }
    //i = 0;
    //while (i < data->number_of_philosopher)
    //{
    //    pthread_join(thread[i], NULL);
    //}
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    pthread_join(thread[2], NULL);
    pthread_join(thread[3], NULL);
    pthread_join(thread[4], NULL);
}