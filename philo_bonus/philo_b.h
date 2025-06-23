/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:50:38 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/22 20:12:54 by rlamlaik         ###   ########.fr       */
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
#include <semaphore.h>
#include <fcntl.h>   // O_CREAT, O_EXCL

#include <sys/stat.h>
#include <stdio.h>       // printf
#include <stdlib.h>      // malloc, free, exit
#include <string.h>      // memset
#include <unistd.h>      // write, fork, usleep
#include <sys/time.h>    // gettimeofday
#include <sys/wait.h>    // waitpid
#include <signal.h>      // kill
#include <pthread.h>     // pthread_create, pthread_detach, pthread_join
#include <semaphore.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_list 
{
	pid_t			content;
	struct s_list	*next;
}				t_list;

typedef struct s_philo
{
	size_t				id;
	long				last_meal;
	int					eated;
	int					eat_check;
	t_data				*data;
}				t_philo;

typedef struct s_data
{
	t_philo				*philo;
	size_t				number_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	long				number_of_times_each_philo_must_eat;

	sem_t				*forks;
	// sem_t				*meals;
	sem_t				*writing;
	sem_t				*dead;
	t_list				*childs;
	long				start;
}		t_data;

long	get_time(void);
int		parssing(char **av, int ac, t_data*data);
int		strating(t_data *data);
int		init_forks_b(t_data *data);
t_list	*ft_lstnew(pid_t content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	child_routine(t_data *data, int id);

#endif
