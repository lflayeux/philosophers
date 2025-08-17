/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:54:31 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/17 17:23:43 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_second_fork(t_philo *philo)
{
	if (safe_mutex_lock(&(philo->global->print), philo->global))
		return;
	printf("%ld ms [%d] has taken a fork[%d]\n", get_time_in_ms() - philo->global->time_start, philo->number, philo->number -1);
	pthread_mutex_unlock(&(philo->global->print));

}

void	take_first_fork(t_philo *philo)
{
	if (safe_mutex_lock(&(philo->global->print), philo->global))
		return;
	printf("%ld ms [%d] has taken a fork [%d]\n", get_time_in_ms() - philo->global->time_start, philo->number, philo->number % philo->global->total_philo);
	pthread_mutex_unlock(&(philo->global->print));

}
void	routine_eat(t_philo *philo)
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
	printf("%ld ms [%d] is eating\n", get_time_in_ms() - philo->global->time_start, philo->number);
	pthread_mutex_unlock(&(philo->global->print));
	safe_mutex_lock(&(philo->state_mutex), philo->global);
	philo->last_meal = get_time_in_ms();
	philo->meal_eaten += 1;
	pthread_mutex_unlock(&(philo->state_mutex));
	ft_usleep(philo->global->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}
void	routine_think(t_philo *philo)
{
	// long time_to_think;

	// time_to_think = philo->global->time_to_die - ((get_time_in_ms() - philo->last_meal) - philo->global->time_to_eat) / 2;
	// printf("tine_to_think: %ld\n", time_to_think);
	// if (time_to_think < 0)
	// 	time_to_think = 0;
	// ft_usleep(time_to_think);
	if (safe_mutex_lock(&(philo->global->print), philo->global))
		return;
	printf("%ld ms [%d] is thinking\n",  get_time_in_ms() - philo->global->time_start ,philo->number);
	pthread_mutex_unlock(&(philo->global->print));
		
}

void	routine_sleep(t_philo *philo, t_shared *global)
{
	
	if (safe_mutex_lock(&(philo->global->print), global))
		return;
	printf("%ld ms [%d] is sleeping\n",  get_time_in_ms() - philo->global->time_start ,philo->number);
	pthread_mutex_unlock(&(philo->global->print));
	ft_usleep(global->time_to_sleep);
}

void *routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while ((philo->global->stop) == FALSE)
	{
		routine_eat(philo);
		routine_think(philo);
		routine_sleep(philo, philo->global);
	}
    return NULL;
}
