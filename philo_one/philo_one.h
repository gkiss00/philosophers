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
    int             id;
    int             *alive;
    int             nb_meal;
    long int        last_meal;
    int             fork_left_id;
    int             fork_right_id;
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
    pthread_mutex_t *write;
    long int        start;
}               s_philosof;

typedef struct  s_struct
{
    int     number_of_philosopher;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     number_of_time_each_philosophers_must_eat;
}               s_data;

//Gestion erreurs
int         ft_error(int argc, char **argv);


//Simulation
void        begin_simulation();

//Actions
void        ft_sleep(s_philosof  *philo);
void        ft_eat(s_philosof  *philo);
void        ft_think(s_philosof  *philo);


//Utils
int         ft_strlen(char *str);
int         is_num(char c);
void        ft_putstr(char *str);
void        ft_putnbr(long int nb);
void        put_message(s_philosof *philo, char *msg);
int         ft_atoi(char *str);

long int    get_time();
long int    get_time_dif_l(long int start);
long int    get_time_dif_ll(long int start, long int actual);
long int    get_time_dif(struct timeval start);

#endif