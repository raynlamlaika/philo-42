/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:44:49 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/18 06:02:11 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include <sys/time.h>
#include <limits.h>


typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				max_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long	last_eat;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	int         	simulation_stopped;
	pthread_mutex_t print_mutex;
	int				someone_died;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
	pthread_mutex_t	write_mutex;

	t_philo			*philos;
}					t_data;


int	check_args(int ac, t_data *philos);
int	parssing(int ac, char **av, t_data *philos);
void *philo_routine(void *arg);

long get_time();
/*utils from libft*/
int	ft_atoi(const char *str, t_data *philos);
char	*ft_itoa(int n);
int	ft_strncmp(const char *str1, const char *str2, size_t num);
int	ft_isdigit(int c);
size_t	ft_strlen(const char *str);

/*helpersss*/
void	print_philos(t_data	*info);


#endif
