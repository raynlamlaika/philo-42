/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 23:15:23 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/19 10:59:56 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	is_passed(char *str, char *sec)
{
	int	i;

	i = 0;
	while (str[i] || sec[i])
	{
		if (str[i] != sec[i])
			return (0);
		i++;
	}
	return (1);
}

int	move(t_list **stack_a, t_list **stack_b, char *str)
{
	if (is_passed(str, "pa"))
		push_a(stack_a, stack_b);
	else if (is_passed(str, "sa"))
		swap_a(stack_a);
	else if (is_passed(str, "sb"))
		swap_b(stack_b);
	else if (is_passed(str, "ss"))
		swap_ab(stack_b, stack_a);
	else if (is_passed(str, "pb"))
		push_b(stack_b, stack_a);
	else if (is_passed(str, "ra"))
		rotate_a(stack_a);
	else if (is_passed(str, "rb"))
		rotate_b(stack_b);
	else if (is_passed(str, "rr"))
		rotate_ab(stack_a, stack_b);
	else if (is_passed(str, "rra"))
		reverse_rotate_a(stack_a);
	else if (is_passed(str, "rrb"))
		reverse_rotate_b(stack_b);
	else if (is_passed(str, "rrr"))
		reverse_rotate_ab(stack_a, stack_b);
	else
		return (write(2, "Error\n", 7), 0);
	return (1);
}

int	search_search(char *str)
{
	if (is_passed(str, "pa\n") || is_passed(str, "sa\n") || \
		is_passed(str, "sb\n") || is_passed(str, "ss\n") || \
		is_passed(str, "pb\n") || is_passed(str, "ra\n") || is_passed(str, "rb\n") \
		|| is_passed(str, "rr\n") || is_passed(str, "rra\n") || \
		is_passed(str, "rrb\n") || is_passed(str, "rrr"))
		return (1);
	else
		return (write(2, "Error\n", 7), 0);
}
