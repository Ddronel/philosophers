/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <dronel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:41:40 by dronel            #+#    #+#             */
/*   Updated: 2022/01/18 16:44:22 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_philo {
	pthread_t		thread;
	int				id;
	int				count_eat;
	int				left;
	int				right;
	long int		last_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table {
	int				count_philo;
	int				count_eat;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		start;
	pthread_t		death;
	t_philo			*philo;
	sem_t			fork;
	sem_t			text;
}	t_table;
//parser
int		parser(int argc, char **argv, t_table *table);
void	ft_error(int error);
//philo_utils
void	*check_death(void *args);
//void	*ft_simulation(t_philo *philo, char *str);
void	*ft_ft(void *args);
long	get_time(void);
void	control_time(long time);

void	create_thread(t_table *table);
void	init_philo(t_table *table);

#endif
