/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:43 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/07 14:03:06 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->nbr_philos >= i)
	{
		

		i++;
	}
}




int	main(int ac, char **av)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(*philos));
	parssing(ac, av, philos);
	printf("parse step: number of philos :%d --> time to die :%d --> time to sleep :%d --> opsionial {philos must eat :%d}\n"
		, philos->nbr_philos, philos->time_to_die,  philos->time_to_sleep, philos->philo_must_eat);
	

	return (0);
}
