/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:43 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/09 07:52:21 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_forks(t_data *philos)
{
	int	i;

	i = 0;
	philos->forks = malloc(sizeof(pthread_mutex_t) * philos->nbr_philos);
	if (!philos->forks)
		return (write(2, "malloc are filed\n", 17), 1);
	while (philos->nbr_philos > i)
	{
		int y = pthread_mutex_init(&philos->forks[i],NULL);
		printf("the init of the forks are passed %d\n", y);
		i++;
	}
}


int	main(int ac, char **av)
{
	int		i;
	t_data	*philos;

	philos = malloc(sizeof(*philos));
	parssing(ac, av, philos);
	printf("parse step: number of philos :%d --> time to die :%d --> time to sleep :%d --> opsionial {philos must eat :%d}\n"
		, philos->nbr_philos, philos->time_to_die,  philos->time_to_sleep, philos->philo_must_eat);

		
	init_forks(philos);
	init_philos();
	free(philos->forks);
	free(philos);
	return (0);
}
