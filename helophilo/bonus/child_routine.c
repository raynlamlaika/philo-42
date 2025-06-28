/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 04:25:40 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/28 18:02:44 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	*check_death(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		sem_wait(philo->meal_lock);
		size_t i = (get_time() - philo->last_meal);
		if ( i > philo->data->time_to_die)
		{
			printf("this i the last :%zu  n %zu %ld\n", i, philo->last_meal , get_time());
			sem_wait(philo->data->writing);
			printf("%zu %lu died\n", get_time() - philo->data->start, philo->id + 1);
			exit(1);
		}
		sem_post(philo->meal_lock);
		// ft_usleep(100, philo);
	}
	return (NULL);
}

int	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->writing);
	printf("%zu %lu has taken a fork\n", get_time() - philo->data->start, philo->id + 1);
	sem_post(philo->data->writing);

	sem_wait(philo->data->forks);
	sem_wait(philo->data->writing);
	printf("%zu %lu has taken a fork\n", get_time() - philo->data->start, philo->id + 1);
	sem_post(philo->data->writing);
	return (1);
}

int	eating(t_philo *philo)
{
	sem_wait(philo->meal_lock);
	philo->last_meal = get_time();
	sem_post(philo->meal_lock);

	sem_wait(philo->data->writing);
	printf("%zu %lu is eating\n", get_time() - philo->data->start, philo->id + 1);
	sem_post(philo->data->writing);

	ft_usleep(philo->data->time_to_eat, philo);

	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (1);
}

void	ft_usleep(size_t time, t_philo *philo)
{
	size_t	start = get_time();

	while ((get_time() - start) <= time)
	{
		sem_wait(philo->meal_lock);
		if ((get_time() - philo->last_meal) > (long)philo->data->time_to_die)
		{
			sem_post(philo->meal_lock);
			return;
		}
		sem_post(philo->meal_lock);
		usleep(150);
	}
}

int	sleeping(t_philo *philo)
{
	sem_wait(philo->data->writing);
	printf("%zu %lu is sleeping\n", get_time() - philo->data->start, philo->id + 1);
	sem_post(philo->data->writing);
	ft_usleep(philo->data->time_to_sleep, philo);//
	return (1);
}

int	thinking(t_philo *philo)
{
	sem_wait(philo->data->writing);
	printf("%zu %lu is thinking\n", get_time() - philo->data->start, philo->id + 1);
	sem_post(philo->data->writing);
	return (1);
}

void	child_routine(t_data *data, int id)
{
	pthread_t	death_checker;
	t_philo		*philo = &data->philo[id];

	philo->id = id;
	philo->eated = 0;
	philo->data = data;
	sem_unlink("/meal_lock");
	philo->meal_lock = sem_open("/meal_lock", O_CREAT, 0644, 1);
	if (philo->meal_lock == SEM_FAILED)
		exit(1);
	sem_wait(philo->meal_lock);
	philo->last_meal = get_time();
	sem_post(philo->meal_lock);

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
