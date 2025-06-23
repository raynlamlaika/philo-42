/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:57:06 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/20 04:24:50 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

static int	ft_overflow(int sing)
{
	if (sing == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sing;
	long	rs;

	i = 0;
	rs = 0;
	sing = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sing *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (rs > (9223372036854775807 - str[i] - 48) / 10)
			return (ft_overflow(sing));
		rs = rs * 10 + str[i] - '0';
		i++;
	}
	return ((int )rs * sing);
}

int	ft_isdigit(int n)
{
	while (n >= '0' && n <= '9')
		return (1);
	return (0);
}

void	add_to(t_data*data, int ac, char**av)
{
	if (ac == 1)
		data->number_of_philos = ft_atoi(av[ac]);
	else if (ac == 2)
		data->time_to_die = ft_atoi(av[ac]);
	else if (ac == 3)
		data->time_to_eat = ft_atoi(av[ac]);
	else if (ac == 4)
		data->time_to_sleep = ft_atoi(av[ac]);
	else if (av[ac])
		data->number_of_times_each_philo_must_eat = ft_atoi(av[ac]);
	else
		data->number_of_times_each_philo_must_eat = -1;
}

int	parssing(char **av, int ac, t_data*data)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac >= 7)
		return (printf("not enoght args\n"), 0);
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '\0')
			return (printf("invalid arg :NULL values are not valid : philosopher\n"), 0);
		while (av[i][j])
		{
			if ((ft_isdigit(av[i][j]) == 0 && av[i][j] != '+' )|| ft_atoi(av[i]) == 0)
				return (printf("invalid arg :`%s`: philosopher\n", av[i]), 0);
			if (av[i][j] == '+')
			{
				if (av[i][++j] == '+')
					return (printf("invalid arg :`%s`: philosopher\n", av[i]) \
					, 0);
			}
			j++;
		}
		add_to(data, i++, av);
	}
	return (1);
}
