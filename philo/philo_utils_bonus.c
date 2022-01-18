/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <dronel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:40:02 by dronel            #+#    #+#             */
/*   Updated: 2022/01/18 16:40:02 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <dronel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:16:35 by dronel            #+#    #+#             */
/*   Updated: 2022/01/17 20:13:19 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	control_time(long time)
{
	long	t;
	
	t = get_time() + time;
	usleep((time - 10) * 1000);
	while (get_time() < t)
		usleep(500);
}

void	*check_death(void *args)
{
	t_table		*table;
	int			count;
	long int	sum;
	
	table = (t_table *) args;
	while (1)
	{
		count = -1;
		while (++count < table->count_philo)
		{
			sum = get_time() - table->philo[count].last_eat;
			if (sum > table->time_to_die && table->philo[count].count_eat != 0)
			{
				pthread_mutex_lock(table->text);
				printf("%lu %d is died \n", (get_time() - \
				table->start), table->philo[count].id);
				return (NULL);
			}
			if (sum > table->time_to_die && table->philo[count].count_eat == 0)
			{
				printf("All philosophers ate\n");
				return (NULL);
			}
		}
	}
}

static void	*ft_simulation(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->table->text);
	printf("%lu %d is %s \n", (get_time() - philo->table->start), \
	philo->id, str);
	pthread_mutex_unlock(philo->table->text);
	return (NULL);
}

void	*ft_ft(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *) args;
	philo->last_eat = philo->table->start;
	while (1)
	{
		if (--philo->count_eat != 0)
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
		}
		else
			break ;
	}
	return (0);
}
