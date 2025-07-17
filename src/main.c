/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:12:31 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/17 11:16:33 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philo.h"

int main (int argc, char **argv)
{
	if (argc < 5)
	{
		fprintf(stderr, "Usage: %s <num_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n", argv[0]);
		return 1;
	}
	printf("philo\n");
	return 0;
}