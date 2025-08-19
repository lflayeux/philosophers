/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:14:58 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/19 14:29:05 by lflayeux         ###   ########.fr       */
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
int is_philo_dead(t_table *global, long now, int i)
{
	if ((now - global->philo[i]->last_meal) > global->time_to_die)
	{
		safe_mutex_lock(&(global->print), global);
		printf("%ld %d died\n", now - global->start_time, global->philo[i]->number);
		pthread_mutex_unlock(&(global->print));
		pthread_mutex_lock(&(global->stop_mutex));
		global->simulation_stop = 1;
		pthread_mutex_unlock(&(global->stop_mutex));
		pthread_mutex_unlock(&(global->philo[i]->state_mutex));
		return (1);
	}
	return (0);
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
			if (is_philo_dead(global, now, i))
				return (NULL);
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
