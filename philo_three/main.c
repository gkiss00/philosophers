/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/14 15:31:11 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		g_n_p = 0;
int		g_time_to_die = 0;
int		g_time_to_eat = 0;
int		g_time_to_sleep = 0;
int		g_me = -1;

static void		ft_fill_data(int argc, char **argv)
{
	g_n_p = ft_atoi(argv[1]);
	g_time_to_die = ft_atoi(argv[2]);
	g_time_to_eat = ft_atoi(argv[3]);
	g_time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_me = ft_atoi(argv[5]);
}

int				main(int argc, char **argv)
{
	if (ft_error(argc, argv) == -1)
		return (0);
	ft_fill_data(argc, argv);
	if (g_n_p < 2 || g_n_p > 300)
	{
		ft_putstr("Il doit y avoir entre 2 et 300 philosophes\n");
		return (0);
	}
	begin_simulation();
	return (0);
}
