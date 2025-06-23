/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:54:52 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/23 10:30:08 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(t_data *data)
{
	(void)data;
	return ;
}

void	*ft_printf(t_philo *philo, char*str)
{
	long	i;

	if (philo->eat_check == 1)
	{
		return (NULL);
	}
	pthread_mutex_lock(&philo->data->dead_helper);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_helper);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->dead_helper);
	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->m_time_eat);
	i = get_time() - philo->data->start;
	pthread_mutex_unlock(&philo->m_time_eat);
	printf("time : `%ld` id: %zu %s \n", i, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
	return ("1");
}

int	must_eated(t_philo philo)
{
	if (philo.data->number_of_times_each_philo_must_eat == -1)
		return (1);
	else if (philo.data->number_of_times_each_philo_must_eat <= philo.eated)
		return (0);
	return (0);
}

int	clearing(t_data*data)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_helper);
	pthread_mutex_destroy(&data->write);
	while (data->number_of_philos >= i)
	{
		pthread_mutex_destroy(&data->philo->left_fork[i]);
		pthread_mutex_destroy(&data->philo->right_fork[i]);
		pthread_mutex_destroy(&data->philo[i].m_time_eat);
		pthread_mutex_destroy(&data->philo[i].eated_check);
		i++;
	}
	free(data->forks);
	free(data->philo);
	free(data);
	return (1);
}
