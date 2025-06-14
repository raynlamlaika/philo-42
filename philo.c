/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 02:11:46 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/14 18:20:29 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	size_t	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->forks)
		return (write(2, "malloc are filed\n", 17), 1);
	while (data->number_of_philos > i)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (free(data), free(data->forks), exit(1), 0);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->dead_helper, NULL);
	return (1);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	realstart(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	data->start = get_time();
	while (i < data->number_of_philos)
	{
		data->philo[i].last_time_eat = data->start;
		if (pthread_create(&data->philo[i].philo, \
			NULL, philo_routine, &data->philo[i]) != 0)
			return (write(2, "Thread creation failed\n", 23), 0);
		i++;
	}
	j = 0;
	if (pthread_create(&data->checker, NULL, die, data->philo) != 0)
		return (free(data), 0);
	while (j < data->number_of_philos)
	{
		pthread_join(data->philo[j].philo, NULL);
		j++;
	}
	pthread_join(data->checker, NULL);
	return (1);
}

int	init_philo(t_data *data)
{
	size_t	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philo)
		return (free(data->philo), free(data), exit(1), 0);
	while (i < data->number_of_philos)
	{
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % \
			data->number_of_philos];
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].m_time_eat, NULL);
		i++;
	}
	if (data->start == -1)
		return (free(data->philo), free(data->forks), free(data), 0);
	realstart(data);
	return (1);
}

void	stating(t_data *data)
{
	init_forks(data);
	data->dead = 0;
	init_philo(data);
}

int	main(int ac, char**av)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	if (!data)
		return (1);
	if (parssing(av, ac, data) == 0)
		return (free(data), 0);
	stating(data);
	return (0);
}
