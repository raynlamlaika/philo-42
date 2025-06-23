/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:50:12 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/20 04:39:42 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int main(int ac, char**av)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	if (!data)
		return (1);
	if (parssing(av, ac, data) == 0)
		return (free(data), 0);
	strating(data);
}