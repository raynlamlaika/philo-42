/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:27:04 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/10 17:11:35 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void think(t_data *philo)
// {
// 	printf("philo %d is thinking ...\n", philo->index_philo);
// 	usleep(philo->time_to_sleep * 1000);
// }

// void eat(t_data *philo)
// {
// 	t_data	*helper;

// 	helper = malloc(sizeof(t_data));
// 	if (!helper)
// 		exit(1);
// 	helper = philo;
//     pthread_mutex_lock(philo->philos[helper->index_philo].left_fork);
//     printf("philo %d took left fork\n", philo->index_philo);
//     pthread_mutex_lock(philo->philos[helper->index_philo].right_fork);
//     printf("philo %d took right fork\n", philo->index_philo);
//     printf("philo %d is eating ...\n", philo->index_philo);
//     usleep(philo->time_to_eat * 1000);
//     pthread_mutex_unlock(philo->philos[helper->index_philo].left_fork);
//     pthread_mutex_unlock(philo->philos[helper->index_philo].right_fork);
    
//     printf("philo %d put down forks\n", philo->index_philo);
// }

// void put_forks(t_data *philo)
// {
// 	//pass the helper
// 	t_data *helper;
// 	helper =  malloc(sizeof(t_data));
// 	helper = philo;
// 	pthread_mutex_unlock(philo->philos[helper->index_philo].left_fork);
//     pthread_mutex_unlock(philo->philos[helper->index_philo].right_fork);
// 	printf("philo %d is puting forks ...\n", philo->philos->id);
	
// }
// void take_forks(t_data *philo)
// {
// 	t_data *helper;
// 	helper =  malloc(sizeof(t_data));
// 	helper = philo;

// 	pthread_mutex_lock(philo->philos[helper->index_philo].left_fork);
//     printf("philo %d took left fork\n", philo->philos[helper->index_philo].id);
    
//     pthread_mutex_lock(philo->philos[helper->index_philo].right_fork);
//     printf("philo %d took right fork\n", philo->philos[helper->index_philo].id);
	
// }
// void sleep_philo(t_data *philo)
// {
// 	printf("philo %d is sleeping ...\n", philo->philos->id);
// 	usleep(philo->time_to_sleep * 1000);
// }

// void *philo_routine(void *arg)
// {
// 	t_data	*philos;

// 	philos = (t_data *)arg;
// 	// printf("this is the in %d\n", philos->index_philo);
// 	while (1) 
// 	{
// 		think(philo);
// 		take_forks(philo);
// 		eat(philo);
// 		put_forks(philo);
// 		sleep_philo(philo);
// 	}

// 	return (NULL);
// }

void think(t_data *philo)
{
    printf("philo %d is thinking ...\n", philo->index_philo);
    usleep(philo->time_to_sleep * 1000);
}

void eat(t_data *philo)
{
    pthread_mutex_lock(philo->philos[philo->index_philo].left_fork);
    printf("philo %d took left fork\n", philo->index_philo);

    pthread_mutex_lock(philo->philos[philo->index_philo].right_fork);
    printf("philo %d took right fork\n", philo->index_philo);

    printf("philo %d is eating ...\n", philo->index_philo);
    usleep(philo->time_to_eat * 1000);

    pthread_mutex_unlock(philo->philos[philo->index_philo].left_fork);
    pthread_mutex_unlock(philo->philos[philo->index_philo].right_fork);

    printf("philo %d put down forks\n", philo->index_philo);
}

void put_forks(t_data *philo)
{
    pthread_mutex_unlock(philo->philos[philo->index_philo].left_fork);
    pthread_mutex_unlock(philo->philos[philo->index_philo].right_fork);
    printf("philo %d is putting forks ...\n", philo->index_philo);
}

void take_forks(t_data *philo)
{
    pthread_mutex_lock(philo->philos[philo->index_philo].left_fork);
    printf("philo %d took left fork\n", philo->index_philo);

    pthread_mutex_lock(philo->philos[philo->index_philo].right_fork);
    printf("philo %d took right fork\n", philo->index_philo);
}

void sleep_philo(t_data *philo)
{
    printf("philo %d is sleeping ...\n", philo->index_philo);
    usleep(philo->time_to_sleep * 1000);
}

void *philo_routine(void *arg)
{
    t_data *philos = (t_data *)arg;

    while (1) 
    {
        think(philos);
        take_forks(philos);
        eat(philos);
        put_forks(philos);
        sleep_philo(philos);
    }

    return NULL;
}


