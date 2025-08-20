/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:54:31 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/20 18:55:01 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philosopher_eat(t_philo *philo)
{
	if (!acquire_forks(philo))
		return (FALSE);
	if (!safe_mutex_lock(&(philo->global->print), philo->global))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (FALSE);
	}
	printf("%ld ms [%d] is eating\n",
		current_time_ms() - philo->global->start_time, philo->number);
	pthread_mutex_unlock(&(philo->global->print));
	if (!safe_mutex_lock(&(philo->state_mutex), philo->global))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (FALSE);
	}
	philo->last_meal = current_time_ms();
	philo->meal_eaten += 1;
	pthread_mutex_unlock(&(philo->state_mutex));
	ft_usleep(philo->global->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (TRUE);
}

void	philosopher_think(t_philo *philo)
{
	if (!safe_mutex_lock(&(philo->global->print), philo->global))
		return ;
	printf("%ld ms [%d] is thinking\n",
		current_time_ms() - philo->global->start_time, philo->number);
	pthread_mutex_unlock(&(philo->global->print));
}

void	philosopher_sleep(t_philo *philo, t_table *global)
{
	if (!safe_mutex_lock(&(philo->global->print), global))
		return ;
	printf("%ld ms [%d] is sleeping\n",
		current_time_ms() - philo->global->start_time, philo->number);
	pthread_mutex_unlock(&(philo->global->print));
	ft_usleep(global->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)arg;
	if (!safe_mutex_lock(&(philo->global->stop_mutex), philo->global))
		return (NULL);
	stop = philo->global->simulation_stop;
	pthread_mutex_unlock(&(philo->global->stop_mutex));
	while (stop == FALSE)
	{
		if (!philosopher_eat(philo))
			break ;
		philosopher_think(philo);
		philosopher_sleep(philo, philo->global);
		if (!safe_mutex_lock(&(philo->global->stop_mutex), philo->global))
			return (NULL);
		stop = philo->global->simulation_stop;
		pthread_mutex_unlock(&(philo->global->stop_mutex));
	}
	return (NULL);
}
