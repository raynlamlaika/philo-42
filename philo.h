/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:44:49 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/09 07:46:40 by rlamlaik         ###   ########.fr       */
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


typedef struct s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t print_lock; // Mutex for synchronized printing
	
}					t_data;



typedef struct s_philo
{
	int				id;               // Philosopher ID
	int				meals_eaten;      // How many times this philosopher ate
	t_data			*pdata;             // Pointer to shared simulation data
	pthread_t		thread;          // Philosopher thread
	pthread_mutex_t	*left_fork;       // Left fork mutex
	pthread_mutex_t	*right_fork;      // Right fork mutex
}					t_philo;


int	check_args(int ac, t_data *philos);
int	parssing(int ac, char **av, t_data *philos);



/*utils from libft*/
int	ft_atoi(const char *str, t_data *philos);
char	*ft_itoa(int n);
int	ft_strncmp(const char *str1, const char *str2, size_t num);
int	ft_isdigit(int c);
size_t	ft_strlen(const char *str);

#endif
