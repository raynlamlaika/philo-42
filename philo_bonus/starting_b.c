/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:17:04 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/17 18:31:39 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	init_forks_b(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(data->philo));
	if (!data->philo)
		return (free(data), 0);
	i = sem_unlink("/forks");
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

int	init_philo_b(t_data *data)
{
	int		i;
	pid_t	pid;
	t_list	*lst;

	i = 0;
	lst = malloc(sizeof(t_list));
	while (i <= data->number_of_philos)
	{
		pid = fork();
		if (pid == -1)
			;
		if (pid == 0)
			child_routine();
		else if (i == 0)
			ft_lstnew(pid);
		else
			ft_lstadd_back(pid, lst);
		i++;
	}
}

int	strating(t_data *data)
{
	if (init_forks_b(data) == -1)
		return (-1);
	if (init_philo_b(data) == -1);
		return (-1);
	return (1);
}
