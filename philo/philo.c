/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <dronel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:43:38 by dronel            #+#    #+#             */
/*   Updated: 2022/01/17 15:22:55 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*ft_simulation(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->table->text);
	printf("%lu philo %d is %s \n", (get_time() - philo->table->start), \
	philo->id, str);
	pthread_mutex_unlock(philo->table->text);
	return (NULL);
}

void	control_time(long time)
{
	long	t;

	t = get_time() + time;
	usleep((time - 10) * 1000);
	while (get_time() <= t)
		usleep(500);
}

void	*ft_ft(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	philo->last_eat = philo->table->start;
//	printf("---%ld\n", philo->last_eat);
	while (1)
	{
		if (philo->count_eat != 0)
		{
			pthread_mutex_lock(&philo->table->fork[philo->left]);
			ft_simulation(philo, "take a left fork");
			pthread_mutex_lock(&philo->table->fork[philo->right]);
			ft_simulation(philo, "take a right fork");
			philo->last_eat = get_time();
			ft_simulation(philo, "eating");
			control_time(philo->table->time_to_eat);
			pthread_mutex_unlock(&philo->table->fork[philo->left]);
			pthread_mutex_unlock(&philo->table->fork[philo->right]);
			ft_simulation(philo, "sleeping");
			control_time(philo->table->time_to_sleep);
			ft_simulation(philo, "thinking");
			philo->count_eat--;
		}
		else
			break ;
	}
	return (0);
}

void	init_philo(t_table *table)
{
	int		count;
	int		id;

	count = 0;
	id = 1;
	table->philo = malloc(sizeof(t_philo) * table->count_philo);
	table->fork = (pthread_mutex_t *) malloc(sizeof (pthread_mutex_t)
			* table->count_philo);
	table->text = (pthread_mutex_t *) malloc(sizeof (pthread_mutex_t));
	pthread_mutex_init(table->text, NULL);
	if (!table->philo || !table->fork)
		ft_error();
	while (count < table->count_philo)
	{
		table->philo[count].id = id;
		table->philo[count].count_eat = table->count_eat;
		table->philo[count].left = count;
		if (count == table->count_philo - 1)
			table->philo[count].right = 0;
		else
			table->philo[count].right = count + 1;
		table->philo[count].table = table;
		pthread_mutex_init(&table->fork[count], NULL);
//		table->philo[count].fork = &f[count];
//		printf ("count %d\n", count);
//		printf ("id %d\n", table->philo[count].id);
//		printf ("eat %d\n", table->philo[count].count_eat);
//		printf ("l %d\n", table->philo[count].left);
//		printf ("r %ld\n", table->philo[count].last_eat);
//		printf ("-----\n");
		count++;
		id++;
	}
}

void	*check_death(void *args)
{
	t_table		*table;
	int			count;
	long int	sum;

	table = (t_table *) args;
	while (1)
	{
		count = 0;
		while (count < table->count_philo)
		{
			sum = get_time() - table->philo[count].last_eat;
			if (sum > table->time_to_die)
			{
				pthread_mutex_lock(table->text);
				printf("%lu philo %d is died \n", (get_time() - \
				table->start), table->philo[count].id);
				return (NULL);
			}
			count++;
		}
	}
	return (NULL);
}

void	create_thread(t_table *table)
{
	int			i;

	i = -1;
	table->start = get_time();
	while (++i < table->count_philo)
	{
		if (i % 2 == 0)
			pthread_create(&table->philo[i].thread, NULL, &ft_ft, \
				&table->philo[i]);
		usleep(30);
	}
	i = -1;
//	usleep(30);
	while (++i < table->count_philo)
	{
		if (i % 2 == 1)
			pthread_create(&table->philo[i].thread, NULL, &ft_ft, \
				&table->philo[i]);
		usleep(30);
	}
	pthread_create(&table->death, NULL, &check_death, table);
//	i = 0;
//	while (i < table->count_philo)
//	{
//		pthread_join(table->philo[i].thread, NULL);
//		i++;
//	}
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
//	printf ("%d\n", table->count_philo);
//	printf ("%ld\n", table->time_to_die);
//	printf ("%ld\n", table->time_to_eat);
//	printf ("%ld\n", table->time_to_sleep);
//	printf ("%d\n", table->count_eat);
}
