/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <dronel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:43:38 by dronel            #+#    #+#             */
/*   Updated: 2022/01/17 20:13:19 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_exit(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->count_philo)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(table->text);
}

void	init_philo(t_table *table)
{
	int		count;
	int		id;

	count = -1;
	id = 1;
	table->philo = malloc(sizeof(t_philo) * table->count_philo);
	table->fork = (pthread_mutex_t *) malloc(sizeof (pthread_mutex_t) \
			* table->count_philo);
	table->text = (pthread_mutex_t *) malloc(sizeof (pthread_mutex_t));
	if (!table->philo || !table->fork || !table->text)
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
		if ((pthread_mutex_init(&table->fork[count], NULL)) != 0)
			ft_error(1);
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

	i = -1;
	table->start = get_time();
	if ((pthread_mutex_init(table->text, NULL)) != 0)
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
