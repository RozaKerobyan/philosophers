/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:19:10 by rkerobya          #+#    #+#             */
/*   Updated: 2025/09/01 14:10:34 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo_id
{
	int	id;
	int	num_eat;
	int	last_meal;
	pthread_mutex_t	fork;
	struct s_philo	*before;
	struct s_philo	*next;
	struct s_philo	*table;
}	t_philo_id;

typedef struct s_philo
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_eat;
	int	dead;
	int	full;
	int	start_time;
	pthread_mutex_t	check;
	pthread_mutex_t	print;
	t_philo_id		*philo_id;
}	t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
void    initialize(t_philo *philo);
#endif
