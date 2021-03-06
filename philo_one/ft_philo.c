/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/14 13:49:31 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

extern int	g_n_p;
extern int	g_time_to_die;
extern int	g_time_to_eat;
extern int	g_time_to_sleep;
extern int	g_me;
int			g_alive = 1;
int			g_end = 0;

static void		end_simulation(t_philosof philo[g_n_p], int nb, int i)
{
	while (*philo[0].alive == 1 && g_end == 0)
	{
		if (g_me >= 0)
		{
			nb = 0;
			i = 0;
			while (i < g_n_p)
			{
				if (philo[i].nb_meal >= g_me)
					++nb;
				++i;
			}
			if (nb == g_n_p)
			{
				pthread_mutex_lock(philo->write);
				ft_putstr("Tout les philosophes ont mange ");
				ft_putnbr(g_me);
				ft_putstr(" fois. La simulation prend fin.\n");
				g_end = 1;
				pthread_mutex_unlock(philo->write);
			}
		}
	}
}

static void		*death_controle(void *arg)
{
	t_philosof	*philo;

	philo = (t_philosof*)arg;
	ft_wait_start(philo);
	while (*philo->alive == 1 && g_end == 0 && g_me != 0)
	{
		if (get_time_dif_l(philo->last_meal) / 1000 > g_time_to_die)
		{
			put_message_end(philo, " just died\n");
			*philo->alive = 0;
		}
	}
	return (NULL);
}

static void		*start(void *arg)
{
	t_philosof	*philo;

	philo = (t_philosof*)arg;
	ft_wait_start(philo);
	if (philo->id % 2 == 0)
		usleep((g_time_to_eat + g_time_to_sleep) * 1000 / 2);
	while (*philo->alive == 1 && g_end == 0 && g_me != 0)
	{
		ft_eat(philo);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		ft_sleep(philo);
		ft_think(philo);
		if (g_alive == 1 && g_end == 0 && g_time_to_sleep == 0)
			usleep(g_time_to_eat * 1000 / 2);
	}
	return (NULL);
}

static void		init_phil(t_philosof philo[g_n_p], pthread_mutex_t fork[g_n_p])
{
	int			i;
	long int	start;

	i = 0;
	start = get_time() + 1000000;
	while (i < g_n_p)
	{
		philo[i].id = i + 1;
		philo[i].alive = &g_alive;
		philo[i].nb_meal = 0;
		philo[i].last_meal = start;
		philo[i].fork_left_id = i;
		philo[i].fork_right_id = (i + 1) % g_n_p;
		philo[i].fork_left = &fork[i];
		philo[i].fork_right = &fork[(i + 1) % g_n_p];
		philo[i].write = &fork[g_n_p];
		philo[i].start = start;
		++i;
	}
}

void			begin_simulation(void)
{
	int				i;
	t_philosof		philo[g_n_p];
	pthread_t		phil[g_n_p];
	pthread_t		death[g_n_p];
	pthread_mutex_t	fork[g_n_p + 1];

	i = -1;
	while (++i < g_n_p + 1)
		pthread_mutex_init(&fork[i], NULL);
	init_phil(philo, fork);
	i = -1;
	while (++i < g_n_p)
	{
		pthread_create(&phil[i], NULL, start, (void*)&philo[i]);
		pthread_create(&death[i], NULL, death_controle, (void*)&philo[i]);
	}
	end_simulation(philo, 0, 0);
	i = -1;
	while (++i < g_n_p)
		pthread_join(phil[i], NULL);
	i = -1;
	while (++i < g_n_p + 1)
		pthread_mutex_destroy(&fork[i]);
}
