/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:09:38 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/27 22:43:47 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	putstr(char *string)
{
	int	i;

	i = 0;
	if (!string)
		i += write(1, "(null)", 6);
	else
	{
		while (*string)
		{
			i += putchar(*string);
			string++;
		}
	}
	return (i);
}

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

int	is_valid(char *str, t_list *stack)
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
	helper = ft_itoa(ft_atoi(str, stack));
	if ((ft_strncmp(helper, str, ft_strlen(str)) != 0 && \
	ft_atoi(str, stack) != 0) || j < 1)
		return (0);
	return (1);
}
