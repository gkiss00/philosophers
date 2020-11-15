/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/15 15:43:22 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern int	g_n_p;
extern int	g_alive;

void		init_phil(t_philosof philo[g_n_p])
{
	int			i;
	long int	start;
	sem_t		*fork[2];

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

void		init_ret(t_ret ret[g_n_p])
{
	int		i;

	i = 0;
	while (i < g_n_p)
	{
		ret[i].id = -1;
		ret[i].pid = -1;
		ret[i].ret = -1;
		++i;
	}
}
