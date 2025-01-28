/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_oper_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:00:30 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/20 13:45:25 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_b(t_list **stack_b, t_list **stack_a)
{
	t_list	*top_a;

	if (!*stack_a)
		return ;
	top_a = *stack_a;
	*stack_a = (*stack_a)->next;
	top_a->next = *stack_b;
	*stack_b = top_a;
	putstr("pb\n");
}

//rr : ra and rb at the same time.
int	rotate_ab(t_list **stack_a, t_list **stack_b)
{
	if (!(rotate_a(stack_a)) || !(rotate_b(stack_b)))
		return (0);
	putstr("rr\n");
	return (1);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = new;
}

int	more(t_list *stack)
{
	int	themove;

	themove = 0;
	if (!stack)
		return (0);
	while (stack->next)
	{
		if (*stack->data < *stack->next->data)
			themove--;
		themove++;
		stack = stack->next;
	}
	return (themove);
}
