/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:58:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/24 13:48:01 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork_helper(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	ft_printf(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		pthread_mutex_unlock(&philo->data->dead_helper);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	return (1);
}

int	takefork(t_philo *philo)
{
	if (philo->eated >= philo->data->number_of_times_each_philo_must_eat && \
		philo->data->number_of_times_each_philo_must_eat > 0)
		return (0);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	ft_printf(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->left_fork);
		else
			pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->data->dead_helper);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	if (take_fork_helper(philo) == 0)
		return (0);
	return (1);
}

int	eat_helper(t_philo *philo)
{
	if (philo->eat_check == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->data->dead_helper);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	return (1);
}

int	eating(t_philo*philo)
{
	int	i;

	if (eat_helper(philo) == 0)
		return (0);
	ft_printf(philo, "is eating");
	pthread_mutex_lock(&philo->last_eat);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat);
	i = philo->data->time_to_eat;
	ft_usleep(i, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->m_time_eat);
	pthread_mutex_lock(&philo->eated_check);
	philo->eated++;
	pthread_mutex_unlock(&philo->eated_check);
	if (philo->eated == philo->data->number_of_times_each_philo_must_eat)
		philo->eat_check = 1;
	pthread_mutex_unlock(&philo->m_time_eat);
	return (1);
}

void	*philo_routine(void*philo_c)
{
	t_philo	*philo;

	philo = (t_philo *) philo_c;
	if (philo->id % 2 == 0)
		usleep(100);
	while (ft_helper(philo))
	{
		if (!takefork(philo))
			break ;
		if (!eating(philo))
			break ;
		if (sleeping(philo) == NULL)
			break ;
		if (ft_printf(philo, "is thinking") == NULL)
			break ;
	}
	return (NULL);
}
