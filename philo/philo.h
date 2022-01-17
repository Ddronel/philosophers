/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <dronel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:43:16 by dronel            #+#    #+#             */
/*   Updated: 2022/01/15 17:20:03 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

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
	pthread_mutex_t	*fork;
	pthread_mutex_t	*text;
}	t_table;

int		parser(int argc, char **argv, t_table *table);
void	ft_error(void);

#endif
