/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:58:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/14 18:26:00 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stoped(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->dead_helper);
	result = data->dead;
	pthread_mutex_unlock(&data->dead_helper);
	if (result == 1)
		return (0);
	else
		return (1);
	return (result);
}

void	ft_printf(t_philo *philo, char*str)
{
	int	i;

	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_helper);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	pthread_mutex_lock(&philo->data->write);
	i = get_time() - philo->data->start;
	printf("time : `%d` id: %zu %s \n", i, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

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
	return (1);
}

void	sleeping(t_philo*philo)
{
	ft_printf(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	*die(void*philo_c)
{
	t_philo	*philo;
	size_t	h;
	long	now;

	philo = (t_philo *)philo_c;
	while (1)
	{
		now = get_time();
		pthread_mutex_lock(&philo->m_time_eat);
		h = now - philo->last_time_eat;
		pthread_mutex_unlock(&philo->m_time_eat);
		if (h > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->dead_helper);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->dead_helper);
			pthread_mutex_lock(&philo->data->write);
			h = now - philo->last_time_eat;
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
		if (!stoped(philo->data))
			break ;
		if (!takefork(philo))
			break ;
		if (!eating(philo))
			break ;
		ft_printf(philo, "is thinking");
		size_t start = get_time();
		size_t v = (get_time() - start);
		while (v < philo->data->time_to_sleep)
		{
			if (!stoped(philo->data))
				return (NULL);
			sleeping(philo);
		}
	}
	return (NULL);
}
