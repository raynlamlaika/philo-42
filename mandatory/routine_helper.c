/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:20:36 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/23 10:18:50 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*sleeping(t_philo*philo)
{
	if (philo->eat_check == 1)
		return (NULL);
	if (ft_printf(philo, "is sleeping") == NULL)
		return (NULL);
	usleep(philo->data->time_to_sleep * 1000);
	return ("1");
}

void	*die_helper(t_data *data, int i, size_t h)
{
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
		return (NULL);
	return ("1");
}

void	*die(void *philo_c)
{
	t_data	*data;
	size_t	h;
	int		i;
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
		pthread_mutex_lock(&data->philo[i].m_time_eat);
		h = get_time() - data->philo[i].last_time_eat;
		pthread_mutex_unlock(&data->philo[i].m_time_eat);
		if (die_helper(data, i, h) == NULL)
			return (NULL);
		i = (1 + i) % data->number_of_philos;
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
