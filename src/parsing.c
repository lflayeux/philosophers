/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:52:18 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/18 15:41:45 by lflayeux         ###   ########.fr       */
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

int ft_isnum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_args(int argc, char **argv)
{
	int i;
	int nb;

	i = 1;
	while (i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (FALSE);
		nb = ft_atoi(argv[i]);
		if (nb < 0 || (i == 1 && nb == 0))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
void	print_valid_arg()
{
	printf("\n");
	printf(BOLD_RED "Usage: ./philo " ARGS_MESS RESET);
	printf("\n\n");
	printf(BOLD_RED "\t<num_of_philo>: "	RESET ERROR_ARG_MESS_1 "\n");
	printf(BOLD_RED "\t<time_to_die>: "		RESET ERROR_ARG_MESS "\n");
	printf(BOLD_RED "\t<time_to_eat>: "		RESET ERROR_ARG_MESS "\n");
	printf(BOLD_RED "\t<time_to_sleep>: "	RESET ERROR_ARG_MESS "\n");
	printf(BOLD_RED "\t" OPTION	RESET ERROR_ARG_MESS "\n");

}