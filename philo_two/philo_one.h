#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_philosof
{
    int             id;
    int             *alive;
    int             nb_meal;
    long int        last_meal;
    sem_t           *fork;
    sem_t           *write;
    long int        start;
}               s_philosof;

//Gestion erreurs
int         ft_error(int argc, char **argv);


//Simulation
void        begin_simulation();

//Actions
void        ft_sleep(s_philosof  *philo);
void        ft_eat(s_philosof  *philo);
void        ft_think(s_philosof  *philo);
void        ft_wait_start(s_philosof  *philo);


//Utils
int         ft_strlen(char *str);
int         is_num(char c);
void        ft_putstr(char *str);
void        ft_putnbr(long int nb);
void        put_message(s_philosof *philo, char *msg);
void        put_message_end(s_philosof *philo, char *msg);
int         ft_atoi(char *str);

long int    get_time();
long int    get_time_dif_l(long int start);
long int    get_time_dif(struct timeval start);

#endif