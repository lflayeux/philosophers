/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:01:03 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/12 18:04:12 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void init_struct(t_philo *philo, t_shared *global, int argc, char  **argv)
{
	int	i;

	i = 0;
	(void)philo;
	global->total_philo = ft_atoi(argv[1]);
	global->philo = malloc(global->total_philo * sizeof(t_philo *));
	pthread_mutex_init(&(global->mutex), NULL);
	global->time_to_die = ft_atoi(argv[2]);
	global->time_to_sleep = ft_atoi(argv[4]);
	global->philo_dead = FALSE;
	if (argc == 6)
		global->total_meal = ft_atoi(argv[5]);
	else
		global->total_meal = NONE;
	global->fork = malloc(ft_atoi(argv[1]) * sizeof(int));
	while (i < ft_atoi(argv[1]))
	{
		global->fork[i] = 0;
		i++;
	}
}
