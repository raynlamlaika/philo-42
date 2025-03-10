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


void think(t_thread_data *philo)
{
	
	printf("philo %d is thinking ...\n", philo->philo->id);
	// usleep(philo->info->time_to_think * 1000);
	usleep(rand() % 5000000);
}
void eat(t_thread_data *philo)
{
    // Lock the forks (mutexes) before eating
    pthread_mutex_lock(philo->info->philos[philo->info->philos->id].left_fork);
    printf("philo %d took left fork\n", philo->info->philos[philo->philo->id].id);
    
    pthread_mutex_lock(philo->info->philos[philo->philo->id].right_fork);
    printf("philo %d took right fork\n", philo->info->philos[philo->philo->id].id);
    
    // Eating action - simulate eating by sleeping for the time_to_eat
    printf("philo %d is eating ...\n", philo->info->philos[philo->philo->id].id);
    usleep(philo->info->time_to_eat * 1000); // Sleep for the eating time (in milliseconds)
    
    // Once done eating, unlock the forks
    pthread_mutex_unlock(philo->info->philos[philo->philo->id].left_fork);
    pthread_mutex_unlock(philo->info->philos[philo->philo->id].right_fork);
    
    printf("philo %d put down forks\n", philo->info->philos[philo->philo->id].id);
}

void put_forks(t_thread_data *philo)
{
	pthread_mutex_unlock(philo->info->philos[philo->philo->id].left_fork);
    pthread_mutex_unlock(philo->info->philos[philo->philo->id].right_fork);
	printf("philo %d is puting forks ...\n", philo->info->philos->id);
	
}
void take_forks(t_thread_data *philo)
{
	pthread_mutex_lock(philo->info->philos[philo->philo->id].left_fork);
    printf("philo %d took left fork\n", philo->info->philos[philo->philo->id].id);
    
    pthread_mutex_lock(philo->info->philos[philo->philo->id].right_fork);
    printf("philo %d took right fork\n", philo->info->philos[philo->philo->id].id);
	
}
void sleep_philo(t_thread_data *philo)
{
	printf("philo %d is sleeping ...\n", philo->info->philos->id);
	usleep(philo->info->time_to_sleep * 1000);
}

void *philo_routine(void *arg)
{
	t_philo *philo ;

	philo = (t_philo *)arg;
	if (!philo->id)
		return NULL;
	printf("this is the in %d\n", philo->id);
	while (1) 
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
		// break;
	}

	return (NULL);
}
