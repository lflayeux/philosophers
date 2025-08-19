/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:12:31 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/19 14:56:11 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	lonely_behavior(t_table *global)
{
	if (global->total_philo == 1)
	{
    	printf("0 ms [1] has taken a fork\n");
    	ft_usleep(global->time_to_die);
    	printf("%ld ms [1] died\n", current_time_ms() - global->start_time);
    	return (1);
	}
	return (0);
}
void	run(t_philo *philo, t_table *global)
{
	int i;

	i = 0;
	(void)philo;
	global->start_time = current_time_ms();
	while (i < global->total_philo)
	{
		global->philo[i] = malloc(sizeof(t_philo));
		init_philosopher(global->philo[i], global, i + 1);
		global->philo[i]->last_meal = global->start_time;
		pthread_create(&(global->philo[i]->thread), NULL, philosopher_routine, (void *)global->philo[i]);
		i++;
	}
	pthread_create(&(global->monitor_thread), NULL, monitoring ,(void *)global);
	pthread_join(global->monitor_thread, NULL);
	i = 0;
	while (i < global->total_philo)
	{
		pthread_join(global->philo[i]->thread, NULL);
		i++;
	}
}
void	free_all(t_table *global)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&(global->print));
	pthread_mutex_destroy(&(global->stop_mutex));
	while (i < global->total_philo)
	{
		pthread_mutex_destroy(&(global->forks[i]));		
		pthread_mutex_destroy(&(global->philo[i]->state_mutex));	
		free(global->philo[i]);
		i++;
	}
	free((global->forks));
	free(global->philo);
}
int	main(int argc, char **argv)
{
	t_philo		philo;
	t_table		global;
	
	if (argc < 5 || argc > 6)
		return (print_valid_arg(), ERROR);
	if (check_args(argc, argv) == FALSE)
		return (print_valid_arg(), ERROR);
	init_table(&global, argc, argv);
	if (lonely_behavior(&global))
		return (0);
	run(&philo, &global);
	free_all(&global);
	return (SUCCESS);
}
