#include "philo_one.h"

int n_p = 0;
int time_to_die = 0;
int time_to_eat = 0;
int time_to_sleep = 0;
int me = -1;

static void     ft_fill_data(s_data *data, int argc, char **argv)
{
    n_p = ft_atoi(argv[1]);
    time_to_die = ft_atoi(argv[2]);
    time_to_eat = ft_atoi(argv[3]);
    time_to_sleep = ft_atoi(argv[4]);
    
    data->n_p = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
    {
        me = ft_atoi(argv[5]);
        data->me = ft_atoi(argv[5]);
    }
}

int     main(int argc, char **argv)
{
    s_data  *data;

    if ((data = malloc(sizeof(s_data))) == NULL)
    {
        ft_putstr("Erreur de malloc survenue\n");
        return (0);
    }
    data->me = -1;
    if (ft_error(argc, argv) == -1)
    {
        free(data);
        return (0);
    }
    ft_fill_data(data, argc, argv);
    if (n_p < 2 || n_p > 1000)
    {
        ft_putstr("Il doit y avoir entre 2 et 1000 philosophes\n");
        free(data);
        return (0);
    }
    begin_simulation();
    free(data);
    return (1);
}