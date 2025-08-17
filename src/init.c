/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:01:03 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/17 17:02:17 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philo(t_philo *philo, t_shared *global ,int number)
{
	philo->number = number;
	philo->meal_eaten = 0;
	philo->last_meal = 0;
	philo->first_fork = &(global->fork[(number) % global->total_philo]);
	philo->second_fork  = &(global->fork[number - 1]);
	pthread_mutex_init(&(philo->state_mutex), NULL);
	philo->global = global;
}


void init_struct(t_shared *global, int argc, char  **argv)
{
	int i;

	i = 0;
	global->total_philo = ft_atoi(argv[1]);
	pthread_mutex_init(&(global->print), NULL);
	global->time_to_die = ft_atoi(argv[2]);
	global->time_to_eat = ft_atoi(argv[3]);
	global->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		global->total_meal = ft_atoi(argv[5]);
	else
		global->total_meal = NONE;
	global->stop = FALSE;
	global->time_start = get_time_in_ms();
	global->fork = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	while (i < global->total_philo)
	{
		pthread_mutex_init(&(global->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(global->stop_mutex), NULL);
	global->philo = malloc(global->total_philo * sizeof(t_philo *));
}

// MANQUE LE MONITORING ET LE MUTEX PRINT
