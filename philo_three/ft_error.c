/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/14 15:37:34 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	check_seropositif(int argc, char **argv)
{
	int		i;
	int		j;
	int		tab[argc - 1];

	i = 1;
	j = 0;
	while (i < argc)
	{
		tab[j] = ft_atoi(argv[i]);
		++j;
		++i;
	}
	i = 0;
	while (i < argc - 1)
	{
		if (tab[i] < 0)
			return (-1);
		++i;
	}
	return (0);
}

static int	check_param(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (is_num(argv[i][j]) == -1)
				return (-1);
			++j;
		}
		++i;
	}
	return (0);
}

int			ft_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr("Nb d'arguments invalide\n");
		return (-1);
	}
	if (check_seropositif(argc, argv) == -1)
	{
		ft_putstr("Les parametres doivent etre positifs\n");
		return (-1);
	}
	if (check_param(argc, argv) == -1)
	{
		ft_putstr("Les parametres doivent etre des nombres\n");
		return (-1);
	}
	return (0);
}
