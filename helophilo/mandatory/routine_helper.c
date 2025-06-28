/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:20:36 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/28 15:42:45 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*sleeping(t_philo*philo)
{
	if (philo->eat_check == 1)
		return (NULL);
	if (ft_printf(philo, "is sleeping") == NULL)
		return (NULL);
	ft_usleep(philo->data->time_to_sleep, philo->data);
	return ("1");
}

void	*die_helper(t_data *data, int i, size_t h)
{
	int	j;

	if (h > data->time_to_die || must_eated(data->philo[i]))
	{
		pthread_mutex_lock(&data->dead_helper);
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_helper);
		pthread_mutex_lock(&data->write);
		pthread_mutex_lock(&data->philo->m_time_eat);
		j = get_time() - data->start;
		pthread_mutex_unlock(&data->philo->m_time_eat);
		printf("time : `%d` id: %zu died \n", j, data->philo[i].id);
		pthread_mutex_unlock(&data->write);
		return (NULL);
	}
	pthread_mutex_lock(&data->philo[i].m_time_eat);
	if (data->philo[i].eat_check == 1)
		return (pthread_mutex_unlock(&data->philo[i].m_time_eat), NULL);
	pthread_mutex_unlock(&data->philo[i].m_time_eat);
	return ("1");
}

void	*die(void *philo_c)
{
	t_data	*data;
	int		i;
	int		yyy;
	int		eated;

	(1) && (data = (t_data *)philo_c, i = 0);
	while (1)
	{
		pthread_mutex_lock(&data->philo[i].eated_check);
		eated = data->philo[i].eated;
		pthread_mutex_unlock(&data->philo[i].eated_check);
		if (data->number_of_times_each_philo_must_eat >= 0 && \
			eated > data->number_of_times_each_philo_must_eat)
		{
			i = (1 + i) % data->number_of_philos;
			continue ;
		}
		pthread_mutex_lock(&data->philo[i].last_eat);
		yyy = get_time() - data->philo->last_time_eat;
		pthread_mutex_unlock(&data->philo[i].last_eat);
		if (die_helper(data, i, yyy) == NULL)
			return (NULL);
		(1) && (i = (1 + i) % data->number_of_philos);
	}
	return (NULL);
}

int	ft_helper(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_helper);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	return (1);
}

void	heper(t_data *data, int i)
{
	int	j;

	j = 0;
	clearing(data);
	while (j < i)
		pthread_join(data->philo[j++].philo, NULL);
}
