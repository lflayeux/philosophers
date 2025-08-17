/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:12:31 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/17 17:00:34 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philo.h"
static int	all_ate_enough(t_shared *global)
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
	t_shared	*global = (t_shared *)arg;
	long		now;
	int			i;

	while (!global->stop)
	{
		i = 0;
		while (i < global->total_philo)
		{
			now = get_time_in_ms();
			if ((now - global->philo[i]->last_meal) > global->time_to_die)
			{
				printf("%ld %d died\n", now - global->time_start, global->philo[i]->number);
				pthread_mutex_lock(&(global->stop_mutex));
				global->stop = 1;
				pthread_mutex_unlock(&(global->stop_mutex));
				return (NULL);
			}
			i++;
		}
		if (all_ate_enough(global))
		{
			pthread_mutex_lock(&(global->stop_mutex));
			global->stop = 1;
			pthread_mutex_unlock(&(global->stop_mutex));
			return (NULL);
		}
	}
	return (NULL);
}

void	run(t_philo *philo, t_shared *global)
{
	int i;

	i = 0;
	(void)philo;
	global->time_start = get_time_in_ms();
	if (global->total_philo == 1)
	{
    	printf("0 ms [1] has taken a fork\n");
    	ft_usleep(global->time_to_die);
    	printf("%ld ms [1] died\n", get_time_in_ms() - global->time_start);
    	return ;
	}

	while (i < global->total_philo)
	{
		global->philo[i] = malloc(sizeof(t_philo));
		init_philo(global->philo[i], global, i + 1);
		global->philo[i]->last_meal = global->time_start;
		pthread_create(&(global->philo[i]->thread), NULL, routine, (void *)global->philo[i]);
		i++;
	}
	pthread_create(&(global->monitoring), NULL, monitoring, (void *)global);
	pthread_join(global->monitoring, NULL);
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
	t_shared	global;
	
	if (argc < 5 || argc > 6)
		return (printf("Usage: %s " ARGS "\n", argv[0]), (ERROR));
	if (check_args(argc, argv) == FALSE)
		return (print_valid_arg(), ERROR);
	// TODO ==> parse_error();
	init_struct(&global, argc, argv);
	run(&philo, &global);
	pthread_mutex_destroy(&(global.print));
	return (SUCCESS);
}
