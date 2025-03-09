/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:27:04 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/09 09:31:43 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1) 
	{
		// think(philo);
		// take_forks(philo);
		// eat(philo);
		// put_forks(philo);
		// sleep_philo(philo);
		break ;
	}
	return NULL;
}

