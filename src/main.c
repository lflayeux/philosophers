/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:12:31 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/20 19:37:00 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	run(t_philo *philo, t_table *global)
{
	int	i;

	i = 0;
	(void)philo;
	global->start_time = current_time_ms();
	while (i < global->total_philo)
	{
		global->philo[i] = malloc(sizeof(t_philo));
		init_philosopher(global->philo[i], global, i + 1);
		global->philo[i]->last_meal = global->start_time;
		pthread_create(&(global->philo[i]->thread), NULL,
			philosopher_routine, (void *)global->philo[i]);
		i++;
	}
	pthread_create(&(global->monitor_thread), NULL, monitoring, (void *)global);
	pthread_join(global->monitor_thread, NULL);
	i = 0;
	while (i < global->total_philo)
	{
		pthread_join(global->philo[i]->thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_table		global;

	if (argc < 5 || argc > 6)
		return (print_valid_arg(), ERROR);
	if (check_args(argc, argv) == FALSE)
		return (print_valid_arg(), ERROR);
	if (lonely_behavior(ft_atol(argv[1]), ft_atol(argv[2])))
		return (ERROR);
	init_table(&global, argc, argv);
	run(&philo, &global);
	free_all(&global);
	return (SUCCESS);
}
