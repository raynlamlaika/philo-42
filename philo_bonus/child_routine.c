/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 04:25:40 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/23 08:24:46 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	*check_death(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		// sleep(1000);
		sem_wait(philo->data->dead);
		size_t time = get_time() - philo->data->start;
		// fprintf(stderr, "this  sthe timw  %zu - and the %zu start\n", time , philo->data->time_to_die);
		if (time > philo->data->time_to_die)
		{
			sem_wait(philo->data->writing);
			int y = philo->id + 1;
			printf("%zu %d died\n",time, y);
			exit(1);
		}
		sem_post(philo->data->dead);
		
	}
	return (NULL);
}

int	take_forks(t_philo *philo)
{
	int time;
	int id;

	time =  get_time() - philo->data->start;
	id = philo->id;
	sem_wait(philo->data->writing);
	sem_wait(philo->data->forks);
	printf("%d %d is taking forks\n", time, id);
	sem_post(philo->data->writing);

	sem_wait(philo->data->forks);
	sem_wait(philo->data->writing);
	printf("%d %d is taking forks\n", time, id);
	sem_post(philo->data->writing);
	return (1);
}

int	eating(t_philo *philo)
{
	int time;
	int id;
	time =  get_time() - philo->data->start;
	id = philo->id;
	philo->last_meal = get_time();
	sem_wait(philo->data->writing);
	printf("%d %d is eating\n", time, id);
	sem_post(philo->data->writing);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return(1);
}

int	sleeping(t_philo *philo)
{
	int time;
	int id;

	time =  get_time() - philo->data->start;
	id = philo->id;
	sem_wait(philo->data->writing);
	printf("%d %d is sleeping\n", time, id);
	sem_post(philo->data->writing);
	usleep(philo->data->time_to_sleep * 1000);
	return(1);
}

int	thinking(t_philo *philo )
{
	int time;
	int id;

	time =  get_time() - philo->data->start;
	id = philo->id;
	sem_wait(philo->data->writing);
	printf("%d %d is thinking\n", time, id);
	sem_post(philo->data->writing);
	return(1);
}

void	child_routine(t_data *data, int id)
{
	pthread_t	death_checker;
	t_philo		*philo = &data->philo[id];

	philo->eated = 0;
	philo->id = id;
	philo->last_meal = get_time();
	philo->data = data;

	pthread_create(&death_checker, NULL, check_death, philo);
	pthread_detach(death_checker);
	while (1)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(100);
	}
}
