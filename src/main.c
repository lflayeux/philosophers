/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:12:31 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/08 16:35:23 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	check_args(int argc, char **argv)
{
	int i;
	int nb;

	i = 1;
	while (i < argc)
	{
		nb = ft_atoi(argv[i]);
		if (nb < 0 || (i == 1 && nb == 0))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
void	print_valid_arg()
{
	printf("\nUsage: ./philo " ARGS "\n\n");
	printf("\t<num_of_philo>: must be a positive integer greater than 0\n");
	printf("\t<time_to_die>: must be a positive integer\n");
	printf("\t<time_to_eat>: must be a positive integer\n");
	printf("\t<time_to_sleep>: must be a positive integer\n");
	printf("\t[optional] <number_of_times_each_philosopher_must_eat>: \
			must be a positive integer\n");

}
void init_struct(t_philo *philo, t_shared *global, int argc, char  **argv)
{
	
	(void)philo;
	global->total_philo = ft_atoi(argv[1]);
	global->philo = malloc(global->total_philo * sizeof(t_philo *));
	pthread_mutex_init(&(global->mutex), NULL);
	global->time_to_die = ft_atoi(argv[2]);
	global->time_to_sleep = ft_atoi(argv[4]);
	global->philo_dead = FALSE;
	if (argc == 6)
		global->total_meal = ft_atoi(argv[5]);
	else
		global->total_meal = NONE;
}
void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->global->mutex));
    printf("Je suis le philo : %d\n", philo->number);
	printf("Encore  le philo : %d\n", philo->number);
	pthread_mutex_unlock(&(philo->global->mutex));
    return NULL;
}

void	run(t_philo *philo, t_shared *global)
{
	int i;

	i = 0;
	(void)philo;
	while (i < global->total_philo)
	{
		global->philo[i] = malloc(sizeof(t_philo));
		global->philo[i]->number = i + 1;
		global->philo[i]->global = global;
		pthread_create(&(global->philo[i]->thread), NULL, routine, (void *)global->philo[i]);
		i++;
	}
	i = 0;
	while (i < global->total_philo)
	{
		pthread_join(global->philo[i]->thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_shared	global;
	
	if (argc < 5 || argc > 6)
		return (printf("Usage: %s " ARGS "\n", argv[0]), (ERROR));
	if (check_args(argc, argv) == FALSE)
		return (print_valid_arg(), ERROR);
	init_struct(&philo, &global, argc, argv);
	run(&philo, &global);
	pthread_mutex_destroy(&(global.mutex));
	return (SUCCESS);
}
