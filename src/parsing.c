/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:52:18 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/13 12:52:19 by pandemonium      ###   ########.fr       */
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