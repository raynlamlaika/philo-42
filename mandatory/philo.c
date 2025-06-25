/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 02:11:46 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/25 15:12:48 by rlamlaik         ###   ########.fr       */
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
			return (free(data->forks), free(data), 0);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->dead_helper, NULL);
	pthread_mutex_init(&data->time_helper, NULL);
	return (1);
}

int	realstart(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	data->start = get_time();
	if (data->start == -1)
		return (free(data->philo), free(data->forks), free(data), 0);
	while (i < data->number_of_philos)
	{
		data->philo[i].last_time_eat = data->start;
		data->philo[i].eated = 0;
		data->philo[i].eat_check = 0;
		if (pthread_create(&data->philo[i].philo, \
			NULL, philo_routine, &data->philo[i]) != 0)
			return (write(2, "Thread creation failed\n", 23), heper(data, i), 0);// destory the old ones if u fail
		i++;
	}
	j = 0;
	if (pthread_create(&data->checker, NULL, die, data) != 0)
		return (free(data), heper(data, i), 0);// destory the old ones if u fail
	while (j < data->number_of_philos)
		pthread_join(data->philo[j++].philo, NULL);
	return (pthread_join(data->checker, NULL), 1);
}

int	init_philo(t_data *data)
{
	size_t	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philo)
		return (free(data), 0);
	while (i < data->number_of_philos)
	{
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % \
			data->number_of_philos];
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].last_eat, NULL);
		data->philo[i].eat_check \
		= pthread_mutex_init(&data->philo[i].eated_check, NULL);
		if (pthread_mutex_init(&data->philo[i].m_time_eat, NULL) != 0)
			return (write(2, "mutex init failed\n", 18), 0);
		i++;
	}
	if (realstart(data))
		return (0);
	clearing(data);
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

	if (ac < 5 || ac >= 7)
		return (printf("not enoght args\n"), 0);
	data = malloc (sizeof(t_data));
	if (!data)
		return (1);
	if (parssing(av, data) == 0)
		return (free(data), 0);
	stating(data);
	return (0);
}
