/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <dronel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:43:22 by dronel            #+#    #+#             */
/*   Updated: 2022/01/17 20:24:16 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(int error)
{
	if (error == 0)
		write(1, "incorrect arguments\n", 20);
	if (error == 1)
		write(1, "mutex error\n", 10);
	if (error == 2)
		write(1, "create thread error\n", 20);
	if (error == 3)
		write(1, "malloc error\n", 20);
	return ;
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] <= 47 || str[i] >= 58)
			return (-1);
		i++;
	}
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		c *= 10;
		c += (str[i] - '0');
		i++;
	}
	if (c > 2147483647)
		return (-1);
	return ((int) c);
}

int	parser(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
	{
		ft_error(0);
		return (0);
	}
	table->count_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->count_eat = ft_atoi(argv[5]) + 1;
	else
		table->count_eat = -2;
	if (table->count_philo == -1 || table->count_philo == 0 \
	|| table->time_to_die == -1 || table->time_to_die == 0 \
	|| table->time_to_eat == -1 || table->time_to_eat == 0 \
	|| table->time_to_sleep == -1 || table->time_to_sleep == 0 \
	|| table->count_eat == -1 || table->count_eat == 0)
	{
		ft_error(0);
		return (0);
	}
	return (1);
}
