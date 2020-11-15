/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/15 15:25:51 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern int	g_n_p;
extern int	g_time_to_eat;
extern int	g_time_to_sleep;
extern int	g_end;

void		ft_fork(int pid[g_n_p], t_philosof philo[g_n_p], t_ret ret[g_n_p])
{
	int	i;

	i = 0;
	while (i < g_n_p)
	{
		if ((pid[i] = fork()) == 0)
		{
			start((void*)&philo[i]);
			exit(*philo->alive);
		}
		else
		{
			ret[i].id = i;
			ret[i].pid = pid[i];
		}
		++i;
	}
}

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
