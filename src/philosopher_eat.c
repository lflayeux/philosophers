/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_eat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:59:23 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/20 19:39:27 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	take_second_fork(t_philo *philo)
{
	if (!safe_mutex_lock(philo->second_fork, philo->global))
		return (FALSE);
	if (!safe_mutex_lock(&(philo->global->print), philo->global))
		return (pthread_mutex_unlock(philo->second_fork), FALSE);
	printf("%ld ms [%d] has taken a fork [%d]\n",
		current_time_ms() - philo->global->start_time,
		philo->number, philo->number -1);
	pthread_mutex_unlock(&(philo->global->print));
	return (TRUE);
}

int	take_first_fork(t_philo *philo)
{
	if (!safe_mutex_lock(philo->first_fork, philo->global))
		return (FALSE);
	if (!safe_mutex_lock(&(philo->global->print), philo->global))
		return (pthread_mutex_unlock(philo->first_fork), FALSE);
	printf("%ld ms [%d] has taken a fork [%d]\n",
		current_time_ms() - philo->global->start_time, philo->number,
		philo->number % philo->global->total_philo);
	pthread_mutex_unlock(&(philo->global->print));
	return (TRUE);
}

int	acquire_forks(t_philo *philo)
{
	if (philo->number % 2 == 0)
	{
		if (philo->meal_eaten == 0)
			ft_usleep(1);
		if (!take_second_fork(philo))
			return (FALSE);
		if (!take_first_fork(philo))
		{
			pthread_mutex_unlock(philo->second_fork);
			return (FALSE);
		}
	}
	else
	{
		if (!take_first_fork(philo))
			return (FALSE);
		if (!take_second_fork(philo))
		{
			pthread_mutex_unlock(philo->first_fork);
			return (FALSE);
		}
	}
	return (TRUE);
}
