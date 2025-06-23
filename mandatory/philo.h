/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 02:12:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/23 10:18:33 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pthread_t			philo;
	size_t				id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long				last_time_eat;
	pthread_mutex_t		m_time_eat;
	int					eated;
	pthread_mutex_t		eated_check;
	int					eat_check;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	t_philo				*philo;
	pthread_t			checker;
	pthread_mutex_t		*forks;
	size_t				number_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	long				number_of_times_each_philo_must_eat;
	pthread_mutex_t		dead_helper;
	int					dead;
	pthread_mutex_t		write;
	long				start;
}		t_data;

int		parssing(char **av, t_data*data);
void	*philo_routine(void *philo_c);
void	*die(void*philo_c);
long	get_time(void);
void	ft_usleep(t_data *data);
void	*ft_printf(t_philo *philo, char*str);
int		must_eated(t_philo philo);
void	*sleeping(t_philo*philo);
void	*die_helper(t_data *data, int i, size_t h);
void	*die(void *philo_c);
int		ft_helper(t_philo *philo);
int		clearing(t_data*data);

#endif
