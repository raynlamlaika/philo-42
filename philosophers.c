/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:27:04 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/18 05:57:19 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void think(t_philo *philo)
// {
// 	printf("philo %d is thinking ...\n", philo->id);
// 	usleep(philo->data->time_to_sleep * 1000);
// }

// void eat(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->left_fork);
// 	printf("philo %d took left fork\n", philo->id);

// 	pthread_mutex_lock(philo->right_fork);
// 	printf("philo %d took right fork\n", philo->id);

// 	printf("philo %d is eating ...\n", philo->id);
// 	philo->last_eat = philo->data->start_time; // or get_current_time();
// 	philo->meals_eaten++;
// 	usleep(philo->data->time_to_eat * 1000);

// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);

// 	printf("philo %d put down forks\n", philo->id);
// }

// void sleep_philo(t_philo *philo)
// {
// 	printf("philo %d is sleeping ...\n", philo->id);
// 	usleep(philo->data->time_to_sleep * 1000);
// }


// void die(philos)
// {
//     ;
// }

// void *philo_routine(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;

// 	// printf("Philo ID        : %d\n", philo->id);
// 	// printf("Meals Eaten     : %d\n", philo->meals_eaten);
// 	// printf("Max Meals       : %d\n", philo->max_eat);
// 	// printf("Last Ate Time   : %lu\n", philo->last_eat);
// 	// printf("Total Philos    : %d\n", philo->data->nbr_philos);
// 	// printf("Time to Die     : %d\n", philo->data->time_to_die);
// 	// printf("Time to Eat     : %d\n", philo->data->time_to_eat);
// 	// printf("Time to Sleep   : %d\n", philo->data->time_to_sleep);
// 	// printf("Must Eat Count  : %d\n", philo->data->philo_must_eat);
// 	// printf("left fork       : %p\n", philo->left_fork);
// 	// printf("right fork      : %p\n", philo->right_fork);
    
//     // while (1) 
//     // {
//     //     // eat(philos);// must max eaten  remove 0 with -5
//     //     // sleep_philo(philos);
//     //     // think(philos);
//     //     // // take_forks(philos);
//     //     // // put_forks(philos);
//     //     // // die(philos);
//     // }
//     while (1)
// 	{
// 		think(philo);
// 		eat(philo);
// 		sleep_philo(philo);
// 	}
//     return NULL;
// }






unsigned long get_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void think(t_philo *philo)
{
	printf("philo %d is thinking ...\n", philo->id);
}

void sleep_philo(t_philo *philo)
{
	printf("philo %d is sleeping ...\n", philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000); // slight delay to reduce deadlock

	pthread_mutex_lock(philo->left_fork);
	printf("philo %d took left fork\n", philo->id);

	pthread_mutex_lock(philo->right_fork);
	printf("philo %d took right fork\n", philo->id);

	printf("philo %d is eating ...\n", philo->id);
	philo->last_eat = get_time_ms();
	philo->meals_eaten++;

	usleep(philo->data->time_to_eat * 1000);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

	printf("philo %d put down forks\n", philo->id);
}

long get_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000)); // milliseconds
}

void die(t_philo *philo)
{
    long current_time = get_time();
    long time_since_last_meal = current_time - philo->last_eat;

    if (time_since_last_meal >= philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d died 💀\n", current_time - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);

        // Signal simulation should stop
        pthread_mutex_lock(&philo->data->dead);
        philo->data->simulation_stopped = 1;
        pthread_mutex_unlock(&philo->data->dead);
    }
}
void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (philo->meals_eaten < philo->max_eat)
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return NULL;
}
