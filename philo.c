/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:45:43 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/06 13:34:39 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* parssinf the params as expected  */
/*  ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]*/

int	is_valid(char *str, t_philo *philos)
{
	int		i;
	int		j;
	char	*helper;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] == '-' || str[i] == '+')
		i++;
	j = 0;
	while (str[i])
	{		
		if (!ft_isdigit(str[i]))
			return (0);
		j++;
		i++;
	}
	helper = ft_itoa(ft_atoi(str, philos));
	if ((ft_strncmp(helper, str, ft_strlen(str)) != 0 && \
	ft_atoi(str, philos) != 0) || j < 1)
		return (0);
	return (1);
}

int	passing_args(int ac, char**av, t_philo *philos)
{
	if (!is_valid(av[1], philos) || !is_valid(av[2], philos) || !is_valid(av[3], philos)|| !is_valid(av[4], philos))
		return (write(2, "argemmnet are not valiiid !!\n", 29),exit(1) ,0);
	if (ac == 6)
		if (is_valid(av[5], philos))
			philos->philo_must_eat = ft_atoi(av[5], philos);
		else
			return (write(2, "argemmnet are not valiiid !!\n", 29),exit(1) ,0);
	philos->nbr_philos = ft_atoi(av[1], philos);
	philos->time_to_die = ft_atoi(av[2], philos);
	philos->time_to_eat = ft_atoi(av[3], philos);
	philos->time_to_sleep = ft_atoi(av[4], philos);
	return (1);
}

int	parssing(int ac, char **av, t_philo *philos)
{
	int i;

	i = 0;
	if (ac == 5 || ac == 6)
		passing_args(ac, av, philos);
	else
		return(write(2,"expected argemmnets :{number_of_philos} {time_to_die} {time_to_eat} {time_to_sleep} {each_philosopher_must_eat}\n", 113), free(philos), exit(1), 0);
	check_args(ac, philos);
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(*philos));
	parssing(ac, av, philos);

	return (0);
}
