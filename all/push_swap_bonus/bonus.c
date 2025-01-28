/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:19:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/24 10:52:13 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static int	take_line(char **str, t_list **stack_a, t_list **stack_b)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = move(stack_a, stack_b, str[i]);
		if (j == 0)
			return (0);
		i++;
	}
	return (1);
}

void	*parce(int ac, char **av, int o, t_list *stack)
{
	t_list	*pp;

	pp = NULL;
	spliting_input(ac, av, &stack);
	pp = stack;
	if (ft_lstsize(stack) < 1)
		return (freed(stack), (write(2, "Error\n", 7)), NULL);
	o = check(stack);
	if (o == 0)
		return (freed(stack), (write(2, "Error\n", 7)), NULL);
	if (o == 2)
		return (freed(stack), NULL);
	switch_int(&pp);
	o = check_double(&stack);
	if (o == 0)
		return ((write(2, "Error\n", 7)), NULL);
	return (stack);
}

int	final_result(t_list *stack_a, t_list *stack_b, int o)
{
	if (o == 0 && ft_lstsize(stack_b) == 0)
		return (freed(stack_a), freed(stack_b), putstr("OK\n"), 1);
	if (o == 1 || ft_lstsize(stack_b) > 0)
		return (freed(stack_a), freed(stack_b), putstr("KO\n"), 1);
	return (1);
}

char	**moooves(int i, t_list *stck, char *er, t_list *stack_b)
{
	char	**moves;
	char	*tmpp;
	char	*next;
	char	*oprt;

	oprt = ft_strdup("");
	if (!oprt)
		return (free(oprt), freed(stck), NULL);
	next = get_next_line(0);
	helper_moves(stck, er, oprt, next);
	while (next)
	{
		i = search_search(next);
		tmpp = oprt;
		oprt = ft_strjoin(oprt, next);
		if (!oprt || i == 0)
			return (freed(stck), freed(stack_b), free(oprt), \
			free(next), free(tmpp), NULL);
		free(tmpp);
		free(next);
		next = get_next_line(0);
	}
	moves = ft_split(oprt, '\n');
	return (free(oprt), free(next), moves);
}

int	main(int ac, char **av)
{
	t_list	*stack_a;
	t_list	*stack_b;
	t_list	*ii;
	int		o;
	char	**moves;

	stack_a = NULL;
	stack_b = NULL;
	o = 0;
	o = 0;
	if (ac < 2)
		return (0);
	stack_a = parce(ac, av, o, stack_a);
	if (!stack_a)
		return (freed(stack_a), freed(stack_b), 0);
	moves = moooves(o, stack_a, "Error\n", stack_b);
	if (!moves)
		return (freed(stack_b), 0);
	o = take_line(moves, &stack_a, &stack_b);
	if (o == 0)
		return (freed(stack_a), freed(stack_b), clean_2(moves), 0);
	clean_2(moves);
	ii = stack_a;
	o = sort_check(&ii);
	return (final_result(stack_a, stack_b, o));
}
