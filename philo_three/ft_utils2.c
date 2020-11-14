/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/14 14:24:23 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

extern int g_end;

long int    get_time()
{
    long int act;
    struct timeval actual;

    gettimeofday(&actual, NULL);
    act = ((actual.tv_sec * 1000000) + actual.tv_usec);
    return (act);
}

long int    get_time_dif_l(long int start)
{
    long int dif;
    struct timeval actual;

    gettimeofday(&actual, NULL);
    dif = ((actual.tv_sec * 1000000) + actual.tv_usec);
    dif -= start;
    return (dif);
}

long int    get_time_dif(struct timeval start)
{
    long int dif;
    struct timeval actual;

    gettimeofday(&actual, NULL);
    dif = ((actual.tv_sec * 1000000) + actual.tv_usec);
    dif -= ((start.tv_sec * 1000000) + start.tv_usec);
    return (dif);
}

void        put_message(t_philosof *philo, char *msg)
{
    sem_wait(philo->write);
    if (*philo->alive == 1 && g_end == 0)
    {
        ft_putnbr(get_time_dif_l(philo->start) / 1000);
        ft_putstr(" : ");
        ft_putnbr(philo->id);
        ft_putstr(msg);
    }
    sem_post(philo->write);
}

void        put_message_end(t_philosof *philo, char *msg)
{
    sem_wait(philo->write);
    if (*philo->alive == 1 && g_end == 0)
    {
        ft_putnbr(get_time_dif_l(philo->start) / 1000);
        ft_putstr(" : ");
        ft_putnbr(philo->id);
        ft_putstr(msg);
        *philo->alive = 0;
    }
    //sem_post(philo->write);
}