/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 02:11:46 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/11 06:18:02 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_overflow(int sing)
{
	if (sing == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sing;
	long	rs;

	i = 0;
	rs = 0;
	sing = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sing *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (rs > (9223372036854775807 - str[i] - 48) / 10)
			return (ft_overflow(sing));
		rs = rs * 10 + str[i] - '0';
		i++;
	}
	return ((int )rs * sing);
}

int ft_isdigit(int n)
{
	while(n >= '0' && n <= '9')
		return 1;
	return 0;
}

void add_to(t_data *data, int ac,char** av)
{
	if (ac == 1)
		data->number_of_philos = ft_atoi(av[ac]);
	else if (ac == 2)
		data->time_to_die = ft_atoi(av[ac]);
	else if (ac == 3)
		data->time_to_eat = ft_atoi(av[ac]);
	else if (ac == 4)
		data->time_to_sleep = ft_atoi(av[ac]);
	else if (av[ac])
		data->number_of_times_each_philo_must_eat = ft_atoi(av[ac]);
	else
		data->number_of_times_each_philo_must_eat = -1;
}

int parssing(char **av, int ac, t_data*data)
{
	int i;
	int j;

	i = 1;
	if (ac < 5 || ac >= 7)
		return (printf("not enoght args\n"),0);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0 && av[i][j] != '+')
				return (printf("invalid arg :`%s`: philosopher\n", av[i]), 0);
			if (av[i][j] == '+')
			{
				if (av[i][++j] == '+')
					return (printf("invalid arg :`%s`: philosopher\n", av[i]), 0);
			}
			j++;
		}
		add_to(data, i , av);
		i++;
	}
	return (1);
}

void print_data(t_data *data)
{
    printf("Number of philosophers: %zu\n", data->number_of_philos);
    printf("Time to die: %zu ms\n", data->time_to_die);
    printf("Time to eat: %zu ms\n", data->time_to_eat);
    printf("Time to sleep: %zu ms\n", data->time_to_sleep);
    printf("Number of times each philosopher must eat: %zu\n",
           data->number_of_times_each_philo_must_eat);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->forks)
		return (write(2, "malloc are filed\n", 17), 1);
	while (data->number_of_philos > i)
    {
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (free(data), free(data->forks), exit(1), 0);
        i++;
    }
	return (1);
}

long get_time()
{
    struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		return(-1);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int stoped(t_data*data)
{
	//|| data->philo->eated >= data->number_of_philos
	if (data->dead)
		return (0);
	return (1);
}

void	takefork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("time : `%ld` id: %zu has taken a fork\n", (get_time() - philo->data->start), philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("time : `%ld` id: %zu has taken a fork\n", (get_time() - philo->data->start), philo->id);
}

void eating(t_philo* philo)
{
	printf("time : `%ld` id: %zu is eating\n", (get_time() - philo->data->start) ,philo->id);
	philo->data->start = get_time() - philo->data->start;
}
	
void sleeping(t_philo* philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->data->time_to_sleep);
}


void die(t_philo* philo)
{
	if (philo->data->time_to_die > philo->data->time_to_sleep)
		philo->data->dead = 1;
		
}


void *philo_routine(void *philo_c)
{
	t_philo* philo = (t_philo *) philo_c;
	while (stoped(philo->data))
	{
		takefork(philo);
		eating(philo);
		sleeping(philo);
		die(philo);
	}
	return NULL;
}

int init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc (sizeof(t_philo));
	if (!data->philo)
		return (free(data->philo), free(data), exit(1), 0);
	while (i < data->number_of_philos)
	{
		data->philo->left_fork = &data->forks[i];
		data->philo->right_fork = &data->forks[(i + 1) % data->number_of_philos];
		data->philo->id = i;
		i++;
	}
	data->start = get_time();
	if (data->start == -1)
		return (free(data->philo), free(data), exit(1), 0);
	i = 0;
	while (i < data->number_of_philos)
	{
		// data->philo[i];
		if (pthread_create(&data->philo[i].philo, NULL, philo_routine, &data->philo[i]) != 0)
				return (write(2, "Thread creation failed\n", 23), 0);
		i++;
	}
	return (1);
}

void stating(t_data *data)
{
	init_forks(data);
	data->dead = 0;
	init_philo(data);
		
}

int main(int ac, char**av)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	if (parssing(av, ac, data) == 0)
		return (free(data), 0);
	print_data(data);
	stating(data);


	return (0);
	
}