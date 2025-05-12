#include "philo.h"


// void print_philos(t_data *info)
// {
//     int i;
//     for (i = 0; i < info->nbr_philos; i++)
//     {
//         printf("  Philosopher %d:\n", info->philos[i].id);
//         printf("\tLeft Fork: %p\n", (void *)info->philos[i].left_fork);   // Print memory address of the left fork (mutex)
//         printf("\tRight Fork: %p\n", (void *)info->philos[i].right_fork);  // Print memory address of the right fork (mutex)
//         printf("\tTimes Eaten: %d\n", info->philos[i].times_ate);
//         printf("\tLast Ate Time: %lu\n\n", info->philos[i].last_ate);
//     }
// }
