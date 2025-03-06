/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:56:47 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/06 12:39:33 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	cheek(int rs, int i, const char *str, t_philo *philos)
{
	long long	overflow;

	overflow = ((long long)((long)rs * 10) + (str[i] - '0'));
	if ((overflow > 2147483647) || (overflow < -2147483648))
	{
		write(1, "Error\n", 7);
		free(philos);
		exit(EXIT_FAILURE);
	}
}

int	ft_atoi(const char *str, t_philo *philos)
{
	int		i;
	int		sing;
	int		rs;

	i = 0;
	rs = 0;
	sing = 1;
	while (str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sing *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		cheek((rs * (long long)sing), i, str, philos);
		rs = rs * 10 + str[i] - '0';
		i++;
	}
	return ((int )rs * sing);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}