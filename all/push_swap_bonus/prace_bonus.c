/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prace_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:29:00 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/27 22:27:38 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	check(t_list *linked)
{
	t_list	*tmp;

	tmp = linked;
	while (tmp)
	{
		if (!is_valid((char *)tmp->data, linked))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	switch_int(t_list **stack_a)
{
	int		i;
	t_list	*curr;

	curr = *stack_a;
	while (curr)
	{
		i = ft_atoi((char *)curr->data, *stack_a);
		free(curr->data);
		curr->data = malloc(sizeof(int));
		if (!(curr->data))
		{
			freed(*stack_a);
			return ;
		}
		*(int *)(curr->data) = i;
		curr = curr->next;
	}
}

int	check_double(t_list **stack)
{
	t_list	*tmp;
	t_list	*pass;

	if (!(stack))
		return (0);
	tmp = *stack;
	while (tmp)
	{
		pass = tmp->next;
		while (pass)
		{
			if (*(tmp->data) == *(pass->data))
				return (freed(*stack), 0);
			pass = pass->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	spliting_input(int ac, char **av, t_list **linked)
{
	int		i;
	int		l;
	t_list	*lst;
	char	**gone;

	i = 1;
	while (ac > i)
	{
		gone = ft_split(av[i++], ' ');
		l = 0;
		while (gone[l])
		{
			lst = ft_lstnew(gone[l++]);
			if (!lst)
			{
				clean_2(gone);
				freed(*linked);
				return ;
			}
			ft_lstadd_back(linked, lst);
		}
		free(gone);
	}
}
