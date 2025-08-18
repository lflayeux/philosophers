/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:12:31 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/18 19:12:12 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philo.h"
static int	all_philosopher_satisfied(t_table *global)
{
	int	i;

	if (global->total_meal == -1)
		return (0);
	i = 0;
	while (i < global->total_philo)
	{
		if (global->philo[i]->meal_eaten < global->total_meal)
			return (0);
		i++;
	}
	return (1);
}


void	*monitoring(void *arg)
{
	t_table	*global = (t_table *)arg;
	long		now;
	int			i;

	while (!global->simulation_stop)
	{
		i = 0;
		while (i < global->total_philo)
		{
			now = current_time_ms();
			safe_mutex_lock(&(global->philo[i]->state_mutex), global);
			if ((now - global->philo[i]->last_meal) > global->time_to_die)
			{
				safe_mutex_lock(&(global->print), global);
				printf("%ld %d died\n", now - global->start_time, global->philo[i]->number);
				pthread_mutex_unlock(&(global->print));
				pthread_mutex_lock(&(global->stop_mutex));
				global->simulation_stop = 1;
				pthread_mutex_unlock(&(global->stop_mutex));
				pthread_mutex_unlock(&(global->philo[i]->state_mutex));
				return (NULL);
			}
			pthread_mutex_unlock(&(global->philo[i]->state_mutex));
			i++;
		}
		if (all_philosopher_satisfied(global))
		{
			pthread_mutex_lock(&(global->stop_mutex));
			global->simulation_stop = 1;
			pthread_mutex_unlock(&(global->stop_mutex));
			return (NULL);
		}
	}
	return (NULL);
}

void	run(t_philo *philo, t_table *global)
{
	int i;

	i = 0;
	(void)philo;
	global->start_time = current_time_ms();
	if (global->total_philo == 1)
	{
    	printf("0 ms [1] has taken a fork\n");
    	ft_usleep(global->time_to_die);
    	printf("%ld ms [1] died\n", current_time_ms() - global->start_time);
    	return ;
	}

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

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_table	global;
	
	if (argc < 5 || argc > 6)
		return (print_valid_arg(), ERROR);
	if (check_args(argc, argv) == FALSE)
		return (print_valid_arg(), ERROR);
	init_table(&global, argc, argv);
	run(&philo, &global);
	pthread_mutex_destroy(&(global.print));
	pthread_mutex_destroy(&(global.stop_mutex));
	return (SUCCESS);
}
