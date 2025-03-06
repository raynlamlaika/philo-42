/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:45:00 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/06 13:34:48 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"


int	check_args(int ac, t_philo *philos)
{
	if (philos->nbr_philos <= 0 || philos->time_to_sleep < 0)
		return(write(2, "in vlaid arg!\n", 15),free(philos), exit(1), 0);
	if (philos->time_to_eat == 0 || philos->time_to_sleep == 0 || philos->time_to_die == 0)
		return (free(philos), exit(0), 0);
	if (ac == 6)
		if (philos->philo_must_eat < 1)
			return (write(2,"number of time not enogh!\n", 27), free(philos), exit(1), 0);
}
