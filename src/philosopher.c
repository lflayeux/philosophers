/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:54:31 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/18 15:05:07 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_second_fork(t_philo *philo)
{
	if (safe_mutex_lock(&(philo->global->print), philo->global))
		return;
	printf("%ld ms [%d] has taken a fork[%d]\n", current_time_ms() - philo->global->start_time, philo->number, philo->number -1);
	pthread_mutex_unlock(&(philo->global->print));

}

void	take_first_fork(t_philo *philo)
{
	if (safe_mutex_lock(&(philo->global->print), philo->global))
		return;
	printf("%ld ms [%d] has taken a fork [%d]\n", current_time_ms() - philo->global->start_time, philo->number, philo->number % philo->global->total_philo);
	pthread_mutex_unlock(&(philo->global->print));

}
void	philosopher_eat(t_philo *philo)
{
	if (philo->number % 2 == 0)
	{
		if (philo->meal_eaten == 0)
			ft_usleep(1);
		take_second_fork(philo);
		take_first_fork(philo);
	}
	else
	{
		take_first_fork(philo);
		take_second_fork(philo);
	}
	if (safe_mutex_lock(philo->second_fork, philo->global))
		return;
	if (safe_mutex_lock(philo->first_fork, philo->global))
		return;
	if (safe_mutex_lock(&(philo->global->print), philo->global))
		return;
	printf("%ld ms [%d] is eating\n", current_time_ms() - philo->global->start_time, philo->number);
	pthread_mutex_unlock(&(philo->global->print));
	safe_mutex_lock(&(philo->state_mutex), philo->global);
	philo->last_meal = current_time_ms();
	philo->meal_eaten += 1;
	pthread_mutex_unlock(&(philo->state_mutex));
	ft_usleep(philo->global->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}
void	philosopher_think(t_philo *philo)
{
	// long time_to_think;

	// time_to_think = philo->global->time_to_die - ((current_time_ms() - philo->last_meal) - philo->global->time_to_eat) / 2;
	// printf("tine_to_think: %ld\n", time_to_think);
	// if (time_to_think < 0)
	// 	time_to_think = 0;
	// ft_usleep(time_to_think);
	if (safe_mutex_lock(&(philo->global->print), philo->global))
		return;
	printf("%ld ms [%d] is thinking\n",  current_time_ms() - philo->global->start_time ,philo->number);
	pthread_mutex_unlock(&(philo->global->print));
		
}

void	philosopher_sleep(t_philo *philo, t_table *global)
{
	
	if (safe_mutex_lock(&(philo->global->print), global))
		return;
	printf("%ld ms [%d] is sleeping\n",  current_time_ms() - philo->global->start_time ,philo->number);
	pthread_mutex_unlock(&(philo->global->print));
	ft_usleep(global->time_to_sleep);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while ((philo->global->simulation_stop) == FALSE)
	{
		philosopher_eat(philo);
		philosopher_think(philo);
		philosopher_sleep(philo, philo->global);
	}
    return NULL;
}
