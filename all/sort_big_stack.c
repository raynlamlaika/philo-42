/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:47:32 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/20 13:38:21 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	chunksize(t_list **stack_a)
{
	int	j;
	int	list_size;

	if (ft_lstsize(*stack_a) >= 400)
		return (j = 45);
	list_size = ft_lstsize(*stack_a);
	return (j = list_size / 6);
}

static void	set_position(t_list *stack)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = stack;
	while (curr)
	{
		curr->position = i;
		i++;
		curr = curr->next;
	}
}

int	max_positon(t_list *stack)
{
	t_list	*tmp;
	t_list	*max;

	tmp = stack;
	max = tmp;
	while (tmp)
	{
		if (*tmp->data > *max->data)
			max = tmp;
		tmp = tmp->next;
	}
	return (max->position);
}

static void	real_sort(t_list **a, t_list **b, int size_of_stack)
{
	int	max_position;

	size_of_stack = ft_lstsize(*b);
	while (size_of_stack)
	{
		set_position(*b);
		max_position = max_positon(*b);
		if (max_position < size_of_stack / 2)
		{
			while ((*b)->position != max_position)
				rotate_b(b);
		}
		else
		{
			while ((*b)->position != max_position)
				reverse_rotate_b(b);
		}
		push_a(a, b);
		size_of_stack--;
	}
}

void	sort_big(int i, t_list **stack_a, t_list **stack_b)
{
	int	chunk;
	int	help;

	help = more(*stack_a);
	chunk = chunksize(stack_a);
	while ((*stack_a))
	{
		if ((*stack_a)->index <= i)
		{
			push_b(stack_b, stack_a);
			i++;
		}
		else if ((*stack_a)->index < (i + chunk))
		{
			push_b(stack_b, stack_a);
			rotate_b(stack_b);
			i++;
		}
		else if (help / 3 > ft_lstsize(*stack_a))
			rotate_a(stack_a);
		else
			reverse_rotate_a(stack_a);
	}
	real_sort(stack_a, stack_b, ft_lstsize(*stack_b));
}
