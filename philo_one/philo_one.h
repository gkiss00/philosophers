/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkiss <gkiss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:24:49 by cochapel          #+#    #+#             */
/*   Updated: 2020/11/14 13:44:34 by gkiss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct		s_philosof
{
	int				id;
	int				*alive;
	int				nb_meal;
	long int		last_meal;
	int				fork_left_id;
	int				fork_right_id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*write;
	long int		start;
}					t_philosof;

int					ft_error(int argc, char **argv);

void				begin_simulation();

void				ft_sleep(t_philosof *philo);
void				ft_eat(t_philosof *philo);
void				ft_think(t_philosof *philo);
void				ft_wait_start(t_philosof *philo);

int					ft_strlen(char *str);
int					is_num(char c);
void				ft_putstr(char *str);
void				ft_putnbr(long int nb);
void				put_message(t_philosof *philo, char *msg);
void				put_message_end(t_philosof *philo, char *msg);
int					ft_atoi(char *str);

long int			get_time();
long int			get_time_dif_l(long int start);
long int			get_time_dif(struct timeval start);

#endif
