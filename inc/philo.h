/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:11:53 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/18 18:18:11 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// ====================================
// ============ INCLUDES ==============
// ====================================

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<pthread.h>
# include	<sys/time.h>

# include	"./colors.h"
# include	"./error.h"

// ====================================
// ============ STRUCTURE =============
// ====================================

typedef struct s_philo	t_philo;

typedef struct s_shared
{
	int					total_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					total_meal;
	int					simulation_stop;
	long				start_time;
	pthread_t			monitor_thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t 	print;
	pthread_mutex_t		stop_mutex;
	t_philo				**philo;
}				t_table;

typedef struct s_philo
{
	pthread_t			thread;
	int					number;
	int					meal_eaten;
	long				last_meal;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		state_mutex;
	t_table			*global;
}				t_philo;

// ====================================
// ============== INIT.C ==============
// ====================================

void	init_table(t_table *global, int argc, char  **argv);
void	init_philosopher(t_philo *philo, t_table *global ,int number);


// ====================================
// ============= PARSING.C ============
// ====================================

void	print_valid_arg();
int		check_args(int argc, char **argv);
int		ft_atoi(char *str);

// ====================================
// =========== PHILOSOPHER.C ==========
// ====================================

void	philosopher_eat(t_philo *philo);
void	*philosopher_routine(void *arg);


// ====================================
// ============== UTILS.C =============
// ====================================

long current_time_ms(void);
void ft_usleep(long time_in_ms);
int safe_mutex_lock(pthread_mutex_t *m, t_table *global);


#endif