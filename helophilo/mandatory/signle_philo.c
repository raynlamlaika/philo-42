/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signle_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:35:44 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/28 00:54:06 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine_single(void *philo_t)
{
	t_philo	*philo;

	philo = (t_philo *)philo_t;
	pthread_mutex_lock(philo->left_fork);
	ft_printf(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_lock(&philo->data->dead_helper);
	if (!philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_helper);
		ft_printf(philo, "died");
		philo->data->dead = 1;
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	return (NULL);
}

void	*sigle_philo(t_data *data)
{
	t_philo	*philo;

	data->start = get_time();
	if (data->start == -1)
		return (free(data->philo), free(data->forks), free(data), NULL);
	philo = &data->philo[0];
	philo->id = 1;
	philo->last_time_eat = data->start;
	philo->eated = 0;
	philo->eat_check = 0;
	philo->data = data;
	philo->left_fork = &data->forks[0];
	if (pthread_create(&philo->philo, NULL, philo_routine_single, philo) != 0)
		return (write(2, "Thread creation failed\n", 23), heper(data, 0), NULL);
	pthread_join(philo->philo, NULL); // Wait for him to die
	// i will clear the rest here

	return ("1");
}
