/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_opr_tow_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 09:58:42 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/20 10:08:24 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	reverse_rotate_a(t_list **stack_a)
{
	t_list	*last;
	t_list	*sec;

	if (!*stack_a || !(*stack_a)->next)
		return (0);
	last = ft_lstlast(*stack_a);
	sec = lst_second(*stack_a);
	last->next = *stack_a;
	*stack_a = last;
	sec->next = NULL;
	return (1);
}

int	reverse_rotate_b(t_list **stack_b)
{
	t_list	*last;
	t_list	*sec;

	if (!*stack_b || !(*stack_b)->next)
		return (0);
	last = ft_lstlast(*stack_b);
	sec = lst_second(*stack_b);
	last->next = *stack_b;
	*stack_b = last;
	sec->next = NULL;
	return (1);
}

void	reverse_rotate_ab(t_list **stack_a, t_list **stack_b)
{
	reverse_rotate_a(stack_a);
	reverse_rotate_b(stack_b);
}

int	rotate_a(t_list **stack_a)
{
	t_list	*top;
	t_list	*last;

	if (!*stack_a || !(*stack_a)->next)
		return (0);
	top = *stack_a;
	*stack_a = top->next;
	last = ft_lstlast(*stack_a);
	last->next = top;
	top->next = NULL;
	return (1);
}

int	rotate_b(t_list **stack_b)
{
	t_list	*botton;
	t_list	*top;

	if (!*stack_b || !(*stack_b)->next)
		return (0);
	top = *stack_b;
	*stack_b = top->next;
	botton = ft_lstlast(*stack_b);
	botton->next = top;
	top->next = NULL;
	return (1);
}
