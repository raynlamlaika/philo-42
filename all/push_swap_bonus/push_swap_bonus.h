/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:13:24 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/27 22:29:04 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# define BUFFER_SIZE 3

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct l_list
{
	int				index;
	int				*data;
	struct l_list	*next;
}					t_list;

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char*source);
int		ft_isdigit(int c);
int		ft_atoi(const char *str, t_list *stck);
int		is_valid(char *c, t_list *stack);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
int		swap_ab(t_list **stack_b, t_list **stack_a);
int		swap_a(t_list **stack_a);
int		swap_b(t_list **stack_b);
void	push_a(t_list **stack_a, t_list **stack_b);
t_list	*lst_second(t_list *lst);
int		rotate_a(t_list **stack_a);
int		rotate_b(t_list **stack_b);
int		rotate_ab(t_list **stack_a, t_list **stack_b);
int		reverse_rotate_a(t_list **stack_a);
t_list	*ft_lstlast(t_list *lst);
int		reverse_rotate_b(t_list **stack_b);
void	reverse_rotate_ab(t_list **stack_a, t_list **stack_b);
void	push_b(t_list **stack_b, t_list **stack_a);
void	spliting_input(int ac, char **av, t_list **linked);
int		check(t_list *linked);
int		putstr(char *string);
void	switch_int(t_list **stack_a);
int		sort_index(t_list *lst);
int		check_double(t_list **stack);
void	freed(t_list *lst);
void	clean_2(char **ptr);
int		sort_check(t_list **stack_a);
int		move(t_list **stack_a, t_list **stack_b, char *str);
int		is_passed(char *str, char *sec);
int		search_search(char *str);
char	*ft_itoa(int n);

#endif