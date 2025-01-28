/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:13:29 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/27 22:41:44 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	clean_2(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	freed(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst->data);
		free(lst);
		lst = tmp;
	}
}

int	sort_check(t_list **stack_a)
{
	t_list	*tmp;

	tmp = *stack_a;
	while (tmp->next)
	{
		if (*tmp->data > *tmp->next->data)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	sort(int size, t_list *stack_a, t_list *stack_b)
{
	int	i;

	i = 0;
	if (size == 2)
		swap_a(&stack_a);
	else if (size == 3)
		sort_three(&stack_a);
	else if (size > 2 && size <= 10)
		sort_small_stack(&stack_a, &stack_b);
	else
		sort_big(i, &stack_a, &stack_b);
	freed(stack_a);
	freed(stack_b);
}

int	main(int ac, char **av)
{
	t_list	*stack_a;
	t_list	*stack_b;
	char	*error;
	int		o;

	error = "Error\n";
	stack_a = NULL;
	stack_b = NULL;
	if (ac < 2)
		return (0);
	spliting_input(ac, av, &stack_a);
	if (check(stack_a) == 0 || (ft_lstsize(stack_a) < 2))
		return (freed(stack_a), write(2, "Erorr\n", 7), 0);
	switch_int(&stack_a);
	o = check_double(&stack_a);
	if (o == 0)
		return ((write(2, error, 7)), 0);
	if (sort_check(&stack_a) == 0)
		return (freed(stack_a), 0);
	sort_index(stack_a);
	sort(ft_lstsize(stack_a), stack_a, stack_b);
}
