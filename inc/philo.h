/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:11:53 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/08 16:40:58 by lflayeux         ###   ########.fr       */
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
	t_philo		**philo;
	pthread_mutex_t mutex;
	pthread_mutex_t *mutex;
	int			total_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			total_meal;
	int			philo_dead;
}				t_shared;

typedef struct s_philo
{
	pthread_t	thread;
	int			number;
	t_shared	*global;
}				t_philo;


#endif