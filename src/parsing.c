/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:52:18 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/20 17:50:32 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_atol(char *str)
{
	int		i;
	long	result;
	int		sign;

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

int	ft_isnum(char *str)
{
	int	i;

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
	int		i;
	long	nb;

	i = 1;
	while (i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (FALSE);
		if (ft_strlen(argv[i]) > 10)
			return (FALSE);
		nb = ft_atol(argv[i]);
		if (nb < 0 || (i == 1 && nb == 0) || nb > 2147483647)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	print_valid_arg(void)
{
	printf("\n");
	printf(BOLD_RED "Usage: ./philo " ARGS_MESS RESET);
	printf("\n\n");
	printf(BOLD_RED "\t<num_of_philo>: " RESET ERROR_ARG_MESS_1 "\n");
	printf(BOLD_RED "\t<time_to_die>: " RESET ERROR_ARG_MESS "\n");
	printf(BOLD_RED "\t<time_to_eat>: " RESET ERROR_ARG_MESS "\n");
	printf(BOLD_RED "\t<time_to_sleep>: " RESET ERROR_ARG_MESS "\n");
	printf(BOLD_RED "\t" OPTION RESET ERROR_ARG_MESS "\n");
}
