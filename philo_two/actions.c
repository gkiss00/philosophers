/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/14 14:19:23 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

extern int	g_time_to_eat;
extern int	g_time_to_sleep;
extern int	g_end;

void		ft_wait_start(t_philosof *philo)
{
	long int	actual;

	actual = get_time();
	while (actual < philo->start)
	{
		actual = get_time();
	}
}

void		ft_eat(t_philosof *philo)
{
	sem_wait(philo->fork);
	put_message(philo, " take his first fork\n");
	put_message(philo, " take his second fork\n");
	put_message(philo, " is eating\n");
	philo->last_meal = get_time();
	usleep(g_time_to_eat * 1000);
	philo->nb_meal += 1;
	philo->last_meal = get_time();
	sem_post(philo->fork);
}

void		ft_sleep(t_philosof *philo)
{
	if (*philo->alive == 1 && g_end == 0)
	{
		put_message(philo, " is sleeping\n");
		usleep(g_time_to_sleep * 1000);
	}
}

void		ft_think(t_philosof *philo)
{
	if (*philo->alive == 1 && g_end == 0)
		put_message(philo, " is thinking\n");
}
