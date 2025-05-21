// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/02 16:45:43 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/21 19:14:41 by rlamlaik         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

void clear(t_data *philo)
{
	int	i;

	i = 0;
	if (philo->forks)
		free(philo->forks);
	if (philo)
		free(philo);
	exit(1);
}


int init_forks(t_data *philos)
{
	int	i;

	i = 0;
	philos->forks = malloc(sizeof(pthread_mutex_t) * philos->nbr_philos);
	if (!philos->forks)
		return (write(2, "malloc are filed\n", 17), 1);
	while (philos->nbr_philos > i)
    {
		// check fail it should ddestroy
		// cech that case where the first will be created but sec it will faild
		pthread_mutex_init(&philos->forks[i],NULL);
        // printf("Fork %d initialized at address: %p\n", i, (void *)&philos->forks[i]);
        i++;
    }
	return (1);
}



int destroy_forks(t_data *philos)
{
	int i = 0;

	while (i < philos->nbr_philos)
    {
		pthread_mutex_destroy(&philos->forks[i]);
        // Optional debug print:
        // printf("Fork %d destroyed at address: %p\n", i, (void *)&philos->forks[i]);
        i++;
    }
	return 1;
}
int	init_philos(t_data	*info)
{
	int	i;

	i = 0;
	info->philos = malloc(sizeof(t_philo) * info->nbr_philos);
	if (!info->philos)
		return (write(2, "failed in creat of philo [allocation]\n", 38),clear(info),0);
	while (i < info->nbr_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].right_fork = &info->forks[(i + 1) % info->nbr_philos];
		info->philos[i].left_fork = &info->forks[i];
		info->philos[i].last_eat = get_time(); // time to start
		info->philos[i].max_eat = info->philo_must_eat;
        info->philos[i].data = info;
		


        // printf("id: %d  right fork %p left one %p\n",info->philos[i].id ,info->philos[i].right_fork , info->philos[i].left_fork);
		// info->philos[i].times_ate = 0;
		i++;
	}
	int y= 0;

	while (y < info->nbr_philos)
	{
		if (pthread_create(&info->philos[y].thread, NULL, philo_routine, &info->philos[y]) != 0)
				return (write(2, "Thread creation failed\n", 23), clear(info), 0);
		y++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*philos;

	philos = malloc(sizeof(*philos));
	philos->philo_must_eat = -1 ; // default init
	parssing(ac, av, philos);
	printf("\nparse step: number of philos :%d --> time to die :%d --> time to eat :%d --> time to sleep :%d {philos must eat : %d}\n\n\n"
		, philos->nbr_philos, philos->time_to_die, philos->time_to_eat ,philos->time_to_sleep, philos->philo_must_eat);
	init_forks(philos);
	init_philos(philos);
	//die(philos);
    for (i = 0; i < philos->nbr_philos; i++)
        pthread_join(philos->philos[i].thread, NULL);
    
    destroy_forks(philos);
	// print_philos(philos);
	free(philos->forks);
	free(philos);
	return (0);
}
