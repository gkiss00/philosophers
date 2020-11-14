/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/14 15:04:29 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

extern int  g_n_p;
extern int  g_time_to_die;
extern int  g_time_to_eat;
extern int  g_time_to_sleep;
extern int  g_me;
int         g_alive = 1;
int         g_end = 0;

static void     *death_controle(void *arg)
{
    t_philosof      *philo;

    philo = (t_philosof*)arg;
    ft_wait_start(philo);
    while(*philo->alive == 1 && g_end == 0 && (g_me > philo->nb_meal || g_me == -1))
    {
        if (get_time_dif_l(philo->last_meal) / 1000 > g_time_to_die)
        {
            put_message_end(philo, " just died\n");
            *philo->alive = 0;
        }    
    }
    return (philo->alive);
}

static void     *start(void *arg)
{
    t_philosof      *philo;
    pthread_t       death;

    philo = (t_philosof*)arg;
    pthread_create(&death, NULL, death_controle, (void*)philo);
    ft_wait_start(philo);
    if (philo->id % 2 == 0)
        usleep((g_time_to_eat + g_time_to_sleep) * 1000 / 2);
    while(*philo->alive == 1 && g_end == 0 && (g_me > philo->nb_meal || g_me == -1))
    {
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
        if (g_alive == 1 && g_end == 0 && g_time_to_sleep == 0)
            usleep(g_time_to_eat * 1000 / 2);
    }
    return (philo->alive);
}

static void    init_phil(t_philosof philo[g_n_p])
{
    int             i;
    long int        start;
    sem_t           *fork[2];

    i = 0;
    start = get_time() + 1000000;
    fork[0] = sem_open("fork", O_CREAT, 0600, g_n_p / 2);
    fork[1] = sem_open("write", O_CREAT, 0600, 1);
    while (i < g_n_p)
    {
        philo[i].id = i + 1;
        philo[i].alive = &g_alive;
        philo[i].nb_meal = 0;
        philo[i].last_meal = start;
        philo[i].fork = fork[0];
        philo[i].write = fork[1];
        philo[i].start = start;
        ++i;
    }
}

static void     *check_end(void  *p)
{
    int     *pid;
    int     ret;

    pid = (int*)p;
    waitpid(*pid, NULL, 0);
    ret = WEXITSTATUS(p);
    kill(*pid, SIGKILL);
    g_end = 1;
    return (NULL);
}

static void     init_pidpid(t_pid pidpid[300])
{
    int     i;
    int     tab[300];


    i = 0;
    while(i < 300)
    {
        tab[i] = -1;
        ++i;
    }
    i = 0;
    while(i < 300){
        pidpid[i].index = -1;
        pidpid[i].pid = -1;
        pidpid[i].ret = tab;
        ++i;
    }
}

void            begin_simulation()
{
    int             i;
    int             pid[g_n_p];
    t_pid           pidpid[300];
    t_philosof      philo[g_n_p];
    pthread_t       ended[g_n_p];

    init_pidpid(pidpid);
    sem_unlink("fork");
    sem_unlink("write");
    init_phil(philo);
    i = -1;
    while (++i < g_n_p)
    {
        if ((pid[i] = fork()) == 0)
        {
            start((void*)&philo[i]);
            exit(*philo[i].alive);
        }
        else
        {
            pidpid[i].index = i;
            pidpid[i].pid = pid[i];
        }
    }
    i = -1;
    while (++i < g_n_p)
        pthread_create(&ended[i], NULL, check_end, (void*)&pid[i]);
    while(g_end == 0)
    {

    }
    i = -1;
    while (++i < g_n_p)
    {
        kill(pid[i], SIGKILL);
    }
    sem_unlink("fork");
    sem_unlink("write");
}