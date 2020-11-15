/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/15 15:42:22 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern int	g_n_p;
extern int	g_time_to_die;
extern int	g_time_to_eat;
extern int	g_time_to_sleep;
extern int	g_me;
int			g_alive = 1;
int			g_end = 0;

static void		*death_controle(void *arg)
{
	t_philosof	*philo;

	philo = (t_philosof*)arg;
	ft_wait_start(philo);
	while (*philo->alive == 1 && g_end == 0
	&& (g_me > philo->nb_meal || g_me == -1))
	{
		if (get_time_dif_l(philo->last_meal) / 1000 > g_time_to_die)
		{
			put_message_end(philo, " just died\n");
			*philo->alive = 0;
		}
	}
	return (philo->alive);
}

void			*start(void *arg)
{
	t_philosof	*philo;
	pthread_t	death;

	philo = (t_philosof*)arg;
	pthread_create(&death, NULL, death_controle, (void*)philo);
	ft_wait_start(philo);
	if (philo->id % 2 == 0)
		usleep((g_time_to_eat + g_time_to_sleep) * 1000 / 2);
	while (*philo->alive == 1 && g_end == 0
	&& (g_me > philo->nb_meal || g_me == -1))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		if (g_alive == 1 && g_end == 0 && g_time_to_sleep == 0)
			usleep(g_time_to_eat * 1000 / 2);
	}
	return (philo->alive);
}

static void		*check_end(void *p)
{
	t_ret	*ret;

	ret = (t_ret*)p;
	wait(&ret->pid);
	ret->ret = WEXITSTATUS(ret->pid);
	g_end = 1;
	return (NULL);
}

static void		does_end(t_ret ret[g_n_p])
{
	int		i;
	int		f;
	int		nb;

	f = 0;
	while (f == 0)
	{
		i = -1;
		nb = 0;
		while (++i < g_n_p)
		{
			if (ret[i].ret == 0)
				f = 1;
			if (ret[i].ret == 1)
				++nb;
			if (nb == g_n_p)
			{
				ft_putstr("All philosopher ate");
				ft_putnbr(g_me);
				ft_putstr(" times\n");
				f = 1;
			}
		}
	}
}

void			begin_simulation(void)
{
	int			i;
	int			pid[g_n_p];
	t_philosof	philo[g_n_p];
	t_ret		ret[g_n_p];
	pthread_t	ended[g_n_p];

	sem_unlink("fork");
	sem_unlink("write");
	init_phil(philo);
	init_ret(ret);
	ft_fork(pid, philo, ret);
	i = -1;
	while (++i < g_n_p)
		pthread_create(&ended[i], NULL, check_end, (void*)&ret[i]);
	does_end(ret);
	while (++i < g_n_p)
		kill(pid[i], SIGKILL);
	sem_unlink("fork");
	sem_unlink("write");
}
