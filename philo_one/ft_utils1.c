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

long int    get_time_dif(struct timeval start)
{
    long int dif;
    struct timeval actual;

    gettimeofday(&actual, NULL);
    dif = ((actual.tv_sec * 1000000) +  actual.tv_usec);
    dif -= ((start.tv_sec * 1000000) +  start.tv_usec);
    return (dif);
}