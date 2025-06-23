/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:17:04 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/23 08:17:42 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	init_forks_b(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philo)
		return (free(data), 0);
	sem_unlink("/forks");
	sem_unlink("/dead");
	sem_unlink("/write");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->number_of_philos);
	if (data->forks == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(1);
	}
	data->writing = sem_open("/write", O_CREAT, 0644, 1);
	if (data->writing == SEM_FAILED)
		return (sem_close(data->forks), sem_unlink("/forks"), perror("sem_open failed"), exit(1), -1);
	data->dead = sem_open("/dead", O_CREAT, 0644, 1);
	if (data->dead == SEM_FAILED)
	{
		(1) && (sem_close(data->writing), sem_unlink("/write"), sem_close(data->forks));
		return (sem_unlink("/forks"), perror("sem_open failed"), exit(1), -1);
	}
	return (1);
}

void kill_all_philos(t_list * list)
{
	while (list)
	{
		kill(list->content, SIGKILL);
		list = list->next;
	}
}

// int	init_philo_b(t_data *data)
// {
// 	size_t		i;
// 	int 	status;
// 	pid_t	pid_child;
// 	t_list	*lst;

// 	i = 0;
// 	lst = malloc(sizeof(t_list));
// 	data->start = get_time();
// 	while (i < data->number_of_philos)
// 	{
// 		pid_child = fork();
// 		if (pid_child == -1)
// 			exit(1);
// 		if (pid_child == 0)
// 			child_routine(data, i);
// 		if (i == 0)
// 			lst = ft_lstnew(pid_child);
// 		else
// 			ft_lstadd_back(&lst, ft_lstnew(pid_child));
// 		i++;
// 	}
// 	for (size_t i = 0; i < data->number_of_philos; i++)
// 	{
// 		pid_child = waitpid(-1, &status, 0);
//     	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
//     	{
// 			kill_all_philos(lst);
// 			break;
//     	}
// 	}
// 	return (1);
// }

int	init_philo_b(t_data *data)
{
	size_t		i = 0;
	int 		status;
	pid_t		pid_child;
	t_list		*lst = NULL;

	data->start = get_time();

	while (i < data->number_of_philos)
	{
		pid_child = fork();
		if (pid_child == -1)
		{
			kill_all_philos(lst);
			exit(1);
		}
		if (pid_child == 0)
			child_routine(data, i);
		
		t_list *new = ft_lstnew(pid_child);
		if (!new)
		{
			kill_all_philos(lst);
			exit(1);
		}
		ft_lstadd_back(&lst, new);
		i++;
	}

	for (size_t j = 0; j < data->number_of_philos; j++)
	{
		pid_child = waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_all_philos(lst);
			break;
		}
	}
	return (1);
}

int	strating(t_data *data)
{
	if (init_forks_b(data) == -1)
		return (-1);
	if (init_philo_b(data) == -1)
		return (-1);
	return (1);
}
