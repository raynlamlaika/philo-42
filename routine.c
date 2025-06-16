/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:58:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/16 11:58:13 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	takefork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->data->dead_helper);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	ft_printf(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_helper);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	ft_printf(philo, "has taken a fork");
	return (1);
}

int	eating(t_philo*philo)
{
	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_helper);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	ft_printf(philo, "is eating");
	pthread_mutex_lock(&philo->m_time_eat);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->m_time_eat);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->eated++;
	if (philo->eated >= philo->data->number_of_times_each_philo_must_eat)
		return (0);
	return (1);
}

void	*sleeping(t_philo*philo)
{
	if (ft_printf(philo, "is sleeping") == NULL)
		return (NULL);
	usleep(philo->data->time_to_sleep * 1000);
	return ("1");
}

void	*die(void*philo_c)
{
	t_philo	*philo;
	size_t	h;

	philo = (t_philo *)philo_c;
	while (1)
	{
		pthread_mutex_lock(&philo->m_time_eat);
		h = get_time() - philo->last_time_eat;
		pthread_mutex_unlock(&philo->m_time_eat);
		if (h > philo->data->time_to_die || must_eated(philo))
		{
			pthread_mutex_lock(&philo->data->dead_helper);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->dead_helper);
			pthread_mutex_lock(&philo->data->write);
			printf("time : `%zu` id: %zu died \n", h, philo->id);
			pthread_mutex_unlock(&philo->data->write);
			return (NULL);
		}
		usleep(500);
	}
	return ("1");
}

void	*philo_routine(void*philo_c)
{
	t_philo	*philo;

	philo = (t_philo *) philo_c;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (!takefork(philo))
			break ;
		if (!eating(philo))
			break ;
		if (ft_printf(philo, "is thinking") == NULL)
			break ;
		if (sleeping(philo) == NULL)
			break ;
	}
	return (NULL);
}
