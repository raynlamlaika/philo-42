/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:46:29 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/27 22:30:20 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static int	alloction(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i += 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	copyintoarray(long nb, size_t i, char *p)
{
	while (nb > 0)
	{
		p[--i] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*p;
	size_t	i;
	long	nb;

	i = alloction(n);
	nb = n;
	p = (char *) malloc(sizeof(char) * (i + 1));
	if (!p)
		return (0);
	p[i] = '\0';
	if (n == 0)
	{
		p[0] = '0';
		return (p);
	}
	if (n < 0)
	{
		nb = -nb;
		p[0] = '-';
	}
	copyintoarray(nb, i, p);
	return (p);
}
