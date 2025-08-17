/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:11:53 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/17 17:02:06 by pandemonium      ###   ########.fr       */
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

// ====================================
// ============ DEFINES ===============
// ====================================

# define	TRUE 1
# define	FALSE 0
# define	SUCCESS 0
# define	ERROR 1
# define	NONE -1
# define	ARGS "<num_of_philo> <time_to_die> <time_to_eat> <time_to_sleep> [optional]: <number_of_times_each_philosopher_must_eat>"


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
	int					stop;
	long				time_start;
	pthread_t			monitoring;
	pthread_mutex_t		*fork;
	pthread_mutex_t 	print;
	pthread_mutex_t		stop_mutex;
	t_philo				**philo;
}				t_shared;

typedef struct s_philo
{
	pthread_t			thread;
	int					number;
	int					meal_eaten;
	long				last_meal;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		state_mutex;
	t_shared			*global;
}				t_philo;

// ====================================
// ============== INIT.C ==============
// ====================================

void init_struct(t_shared *global, int argc, char  **argv);
void	init_philo(t_philo *philo, t_shared *global ,int number);


// ====================================
// ============= PARSING.C ============
// ====================================

void	print_valid_arg();
int		check_args(int argc, char **argv);
int		ft_atoi(char *str);

// ====================================
// =========== PHILOSOPHER.C ==========
// ====================================

void	routine_eat(t_philo *philo);
void	*routine(void *arg);


// ====================================
// ============== UTILS.C =============
// ====================================

long get_time_in_ms(void);
void ft_usleep(long time_in_ms);
int safe_mutex_lock(pthread_mutex_t *m, t_shared *global);


#endif