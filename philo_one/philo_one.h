#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_philosof
{
    int     id;
    int     alive;
}               s_philosof;

typedef struct  s_struct
{
    int     number_of_philosopher;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     number_of_time_each_philosophers_must_eat;
}               s_data;

int     ft_error(int argc, char **argv);

void    begin_experiment(s_data *data);

int     ft_strlen(char *str);
int     is_num(char c);
void    ft_putstr(char *str);
int     ft_atoi(char *str);

#endif