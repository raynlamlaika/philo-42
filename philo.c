/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:43 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/09 09:27:33 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clear(t_data *philo)
{
	int	i;

	i = 0;
	if (philo->forks)
		free(philo->forks);
	if (philo)
		free(philo);
	exit(1);
}


int init_forks(t_data *philos)
{
	int	i;

	i = 0;
	philos->forks = malloc(sizeof(pthread_mutex_t) * philos->nbr_philos);
	if (!philos->forks)
		return (write(2, "malloc are filed\n", 17), 1);
	while (philos->nbr_philos > i)
		pthread_mutex_init(&philos->forks[i++],NULL);
	return (1);
}

int	init_philos(t_data	*info)
{
	int	i;

	i = 0;
	info->philos = malloc(sizeof(t_philo) * info->nbr_philos);
	if (!info->philos)
		return (write(2, "failed in creat of philo [allocation]\n", 38),clear(info),0);
	while (i < info->nbr_philos)
	{
		if (pthread_create(&info->philos[i].thread, NULL, philo_routine, &info->philos[i]) != 0)
			return (write(2, "Thread creation failed\n", 23), clear(info), 0);
		info->philos[i].id = i;
		info->philos[i].right_fork = &info->forks[(i + 1) % info->nbr_philos];
		info->philos[i].left_fork = &info->forks[i];
		info->philos[i].last_ate = 0;
		info->philos[i].times_ate = 0;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*philos;

	philos = malloc(sizeof(*philos));
	philos->philo_must_eat = 0 ;// default init
	parssing(ac, av, philos);
	printf("\nparse step: number of philos :%d --> time to die :%d --> time to eat :%d --> time to sleep :%d {philos must eat : %d}\n\n\n"
		, philos->nbr_philos, philos->time_to_die, philos->time_to_eat ,philos->time_to_sleep, philos->philo_must_eat);
	init_forks(philos);
	init_philos(philos);
	print_philos(philos);
	free(philos->forks);
	free(philos);
	return (0);
}
