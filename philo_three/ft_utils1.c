/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/14 14:21:54 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str != NULL && str[i] != '\0')
    {
        ++i;
    }
    return (i);
}

int is_num(char c)
{
    if (c >= '0' && c <= '9')
        return (0);
    return (-1);
}

void    ft_putstr(char *str)
{
    write(1, (void*)str, ft_strlen(str));
}

void    ft_putnbr(long int nb)
{
    char    tab[20];
    int     div;
    int     i;

    i = 0;
    div = 10;
    if (nb == 0)
    {
        tab[0] = '0';
        ++i;
    }
    while (nb != 0)
    {
        tab[i] = '0' + (nb % div);
        nb /= div;
        ++i;
    }
    while (--i >= 0)
        write(1, &tab[i], 1);
}

int     ft_atoi(char *str)
{
    int i;
    int flag;
    int nb;

    i = 0;
    nb = 0;
    flag = 1;
    if (str[i] == '-')
    {
        flag = -1;
        ++i;
    }
    while (str[i] != '\0')
    {
        nb *= 10;
        nb += str[i] - '0';
        ++i;
    }
    return (nb * flag);
}