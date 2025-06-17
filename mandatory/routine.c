/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:58:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/17 15:14:59 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	takefork(t_philo *philo)
// {
// 	if (philo->eated >= philo->data->number_of_times_each_philo_must_eat && philo->data->number_of_times_each_philo_must_eat > 0)
// 		return (0);
// 	pthread_mutex_lock(&philo->data->dead_helper);
// 	if (philo->data->dead)
// 	{
// 		pthread_mutex_unlock(&philo->data->dead_helper);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(&philo->data->dead_helper);
// 	pthread_mutex_lock(philo->left_fork);
// 	ft_printf(philo, "has taken a fork");
// 	pthread_mutex_lock(&philo->data->dead_helper);
// 	if (philo->data->dead)
// 	{
// 		pthread_mutex_unlock(&philo->data->dead_helper);
// 		pthread_mutex_unlock(philo->left_fork);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(&philo->data->dead_helper);
// 	pthread_mutex_lock(philo->right_fork);
// 	ft_printf(philo, "has taken a fork");
// 	return (1);
// }

int takefork(t_philo *philo)
{
	if (philo->eated >= philo->data->number_of_times_each_philo_must_eat &&
		philo->data->number_of_times_each_philo_must_eat > 0)
		return (0);

	// === Take First Fork ===
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);

	ft_printf(philo, "has taken a fork");

	// === Check if someone died ===
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

	// === Take Second Fork ===
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);

	ft_printf(philo, "has taken a fork");

	// === Check again if someone died ===
	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		// Unlock both forks
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

int	eating(t_philo*philo)
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
	ft_printf(philo, "is eating");
	pthread_mutex_lock(&philo->m_time_eat);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->m_time_eat);
	usleep(philo->data->time_to_eat * 1000);
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

void	*sleeping(t_philo*philo)
{
	if (philo->eat_check == 1)
		return (NULL);
	if (ft_printf(philo, "is sleeping") == NULL)
		return (NULL);
	usleep(philo->data->time_to_sleep * 1000);
	return ("1");
}

void	*die(void *philo_c)
{
	t_data	*data;
	size_t	h;
	int i  = 0;

	data = (t_data *)philo_c;
	while (1)
	{
		pthread_mutex_lock(&data->philo[i].eated_check);
		if (data->number_of_times_each_philo_must_eat >= 0  && data->philo[i].eated > data->number_of_times_each_philo_must_eat)
		{
			i = (1 + i) % data->number_of_philos;
			// pthread_mutex_unlock(&data->philo[i].eated_check);
			continue ;
		}
		pthread_mutex_unlock(&data->philo[i].eated_check);
		pthread_mutex_lock(&data->philo[i].m_time_eat);
		h = get_time() - data->philo[i].last_time_eat;
		pthread_mutex_unlock(&data->philo[i].m_time_eat);
		if (h > data->time_to_die || must_eated(data->philo[i]))
		{
			pthread_mutex_lock(&data->dead_helper);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_helper);
			pthread_mutex_lock(&data->write);
			printf("time : `%zu` id: %zu died \n", h, data->philo[i].id);
			pthread_mutex_unlock(&data->write);
			return (NULL);
		}
		if (data->philo[i].eat_check == 1)
			return(NULL);
		usleep(500);
		i = (1 + i) % data->number_of_philos;
		
	}
	return (NULL);
}

void	*philo_routine(void*philo_c)
{
	t_philo	*philo;

	philo = (t_philo *) philo_c;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!takefork(philo))
			break ;
		if (!eating(philo))
			break ;
		if (sleeping(philo) == NULL)
			break ;
		if (ft_printf(philo, "is thinking") == NULL)
			break ;
		usleep(500);
	}
	return (NULL);
}
