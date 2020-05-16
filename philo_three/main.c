#include "philo_one.h"

int n_p = 0;
int time_to_die = 0;
int time_to_eat = 0;
int time_to_sleep = 0;
int me = -1;

static void     ft_fill_data(int argc, char **argv)
{
    n_p = ft_atoi(argv[1]);
    time_to_die = ft_atoi(argv[2]);
    time_to_eat = ft_atoi(argv[3]);
    time_to_sleep = ft_atoi(argv[4]);

    if (argc == 6)
        me = ft_atoi(argv[5]);
}

int     main(int argc, char **argv)
{
    if (ft_error(argc, argv) == -1)
        return (0);
    ft_fill_data(argc, argv);
    if (n_p < 2 || n_p > 50)
    {
        ft_putstr("Il doit y avoir entre 2 et 50 philosophes\n");
        return (0);
    }
    begin_simulation();
    return (1);
}