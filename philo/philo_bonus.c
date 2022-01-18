/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <dronel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:23:37 by dronel            #+#    #+#             */
/*   Updated: 2022/01/18 17:00:43 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_exit(t_table *table)
{
	int	i;

	i = 0;
	sem_destroy(table->fork[table->count_philo])
	sem_destroy(table->text);
}

void	init_philo(t_table *table)
{
	int		count;
	int		id;

	count = -1;
	id = 1;
	table->philo = malloc(sizeof(t_philo) * table->count_philo);
	if (!table->philo)
		ft_error(3);
	while (++count < table->count_philo)
	{
		table->philo[count].id = id++;
		table->philo[count].count_eat = table->count_eat;
		table->philo[count].left = count;
		if (count == table->count_philo - 1)
			table->philo[count].right = 0;
		else
			table->philo[count].right = count + 1;
		table->philo[count].table = table;
	}
}

static void	philo_create_thread(t_table *table, int i)
{
	if ((pthread_create(&table->philo[i].thread, NULL, &ft_ft, \
			&table->philo[i])) != 0)
		ft_error(2);
}

void	create_thread(t_table *table)
{
	int			i;
	sem_t 		sem;
	i = -1;
	table->start = get_time();
	i = sem_init(&sem, 0, 1)
		ft_error(1);
	while (++i < table->count_philo)
	{
		if (i % 2 == 0)
			philo_create_thread(table, i);
		usleep(30);
	}
	i = -1;
	usleep(30);
	while (++i < table->count_philo)
	{
		if (i % 2 == 1)
			philo_create_thread(table, i);
		usleep(30);
	}
	pthread_create(&table->death, NULL, &check_death, table);
	pthread_join(table->death, NULL);
}

int	main(int argc, char **argv)
{
	t_table		*table;

	table = malloc(sizeof(t_table));
	if (!(parser(argc, argv, table)))
		return (0);
	init_philo(table);
	create_thread(table);
	ft_exit(table);
}