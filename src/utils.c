/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:51:23 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/20 19:35:55 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_all(t_table *global)
{
	int	i;

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

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms)
{
	long	start_time;
	long	now;

	start_time = current_time_ms();
	while (1)
	{
		now = current_time_ms();
		if (now - start_time >= time_in_ms)
			break ;
		usleep(100);
	}
}

int	safe_mutex_lock(pthread_mutex_t *m, t_table *global)
{
	int	simulation_stopped;

	pthread_mutex_lock(&(global->stop_mutex));
	simulation_stopped = global->simulation_stop;
	pthread_mutex_unlock(&(global->stop_mutex));
	if (simulation_stopped)
		return (FALSE);
	if (pthread_mutex_lock(m) != 0)
		return (FALSE);
	return (TRUE);
}

int	lonely_behavior(int nb_philo, int time_to_die)
{
	long	start;

	start = current_time_ms();
	if (nb_philo == 1)
	{
		printf("0 ms [1] has taken a fork\n");
		ft_usleep(time_to_die);
		printf("%ld ms [1] died\n", current_time_ms() - start);
		return (TRUE);
	}
	return (FALSE);
}
