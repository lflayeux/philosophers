/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:14:58 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/20 19:23:33 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	all_philosopher_satisfied(t_table *global)
{
	int		i;
	t_philo	*philo;

	if (global->total_meal == -1)
		return (FALSE);
	i = 0;
	while (i < global->total_philo)
	{
		philo = global->philo[i];
		if (!safe_mutex_lock(&(philo->state_mutex), philo->global))
			return (FALSE);
		if (philo->meal_eaten < global->total_meal)
			return (pthread_mutex_unlock(&(philo->state_mutex)), FALSE);
		pthread_mutex_unlock(&(philo->state_mutex));
		i++;
	}
	return (TRUE);
}

int	is_philo_dead(t_table *global, long now, int i)
{
	t_philo	*philo;

	philo = global->philo[i];
	if ((now - philo->last_meal) > global->time_to_die)
	{
		if (!safe_mutex_lock(&(global->print), global))
			return (TRUE);
		printf("%ld %d died\n", now - global->start_time, philo->number);
		pthread_mutex_unlock(&(global->print));
		pthread_mutex_lock(&(global->stop_mutex));
		global->simulation_stop = 1;
		pthread_mutex_unlock(&(global->stop_mutex));
		pthread_mutex_unlock(&(philo->state_mutex));
		return (TRUE);
	}
	return (FALSE);
}

void	*monitoring(void *arg)
{
	t_table		*global;
	int			i;

	global = (t_table *)arg;
	while (!global->simulation_stop)
	{
		i = 0;
		while (i < global->total_philo)
		{
			safe_mutex_lock(&(global->philo[i]->state_mutex), global);
			if (is_philo_dead(global, current_time_ms(), i))
				return (NULL);
			pthread_mutex_unlock(&(global->philo[i]->state_mutex));
			i++;
		}
		if (all_philosopher_satisfied(global))
		{
			safe_mutex_lock(&(global->stop_mutex), global);
			global->simulation_stop = 1;
			pthread_mutex_unlock(&(global->stop_mutex));
			return (NULL);
		}
	}
	return (NULL);
}
