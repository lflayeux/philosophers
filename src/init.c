/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:01:03 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/20 19:11:24 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philosopher(t_philo *philo, t_table *global, int number)
{
	philo->number = number;
	philo->meal_eaten = 0;
	philo->last_meal = 0;
	philo->first_fork = &(global->forks[(number) % global->total_philo]);
	philo->second_fork = &(global->forks[number - 1]);
	pthread_mutex_init(&(philo->state_mutex), NULL);
	philo->global = global;
}

void	init_table(t_table *global, int argc, char **argv)
{
	int	i;

	i = 0;
	global->total_philo = ft_atol(argv[1]);
	pthread_mutex_init(&(global->print), NULL);
	global->time_to_die = ft_atol(argv[2]);
	global->time_to_eat = ft_atol(argv[3]);
	global->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		global->total_meal = ft_atol(argv[5]);
	else
		global->total_meal = NONE;
	global->simulation_stop = FALSE;
	global->start_time = current_time_ms();
	global->forks = malloc(ft_atol(argv[1]) * sizeof(pthread_mutex_t));
	while (i < global->total_philo)
	{
		pthread_mutex_init(&(global->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(global->stop_mutex), NULL);
	global->philo = malloc(global->total_philo * sizeof(t_philo *));
}
