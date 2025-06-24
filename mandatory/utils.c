/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:54:52 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/24 13:50:21 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t i, t_data*data)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) <= i)
	{
		pthread_mutex_lock(&data->dead_helper);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_helper);
			break ;
		}
		pthread_mutex_unlock(&data->dead_helper);
		usleep(150);
	}
}

void	*ft_printf(t_philo *philo, char*str)
{
	long	i;

	if (philo->eat_check == 1)
		return (NULL);
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
	printf("time : `%ld` id: %zu %s \n", i, philo->id, str);
	pthread_mutex_unlock(&philo->m_time_eat);
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
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->dead_helper);
	while (i <= data->number_of_philos)
	{
		pthread_mutex_destroy(data->philo[i].left_fork);
		pthread_mutex_destroy(data->philo[i].right_fork);
		pthread_mutex_destroy(&data->philo[i].m_time_eat);
		pthread_mutex_destroy(&data->philo[i].eated_check);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
