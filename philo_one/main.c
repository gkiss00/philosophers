#include "philo_one.h"

static void     ft_fill_data(s_data data, int argc, char **argv)
{
    data.number_of_philosopher = ft_atoi(argv[1]);
    data.time_to_die = ft_atoi(argv[2]);
    data.time_to_eat = ft_atoi(argv[3]);
    data.time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data.number_of_time_each_philosophers_must_eat = ft_atoi(argv[5]);
}

int     main(int argc, char **argv)
{
    s_data  data;

    data.number_of_time_each_philosophers_must_eat = -1;
    if (ft_error(argc, argv) == -1)
        return (0);
    ft_fill_data(data, argc, argv);
    begin_experiment(data);
    return (1);
}