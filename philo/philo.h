/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:19:10 by rkerobya          #+#    #+#             */
/*   Updated: 2025/10/04 18:10:53 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK 0
# define EAT  1
# define SLEEP 2
# define THINK 3
# define DIE   4

typedef struct s_philo
{
	int				id;
	int				num_eat;
	size_t			last_meal;
	pthread_mutex_t	fork;
	struct s_philo	*before;
	struct s_philo	*next;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				dead;
	int				full;
	size_t			start_time;
	pthread_mutex_t	check;
	pthread_mutex_t	print;
	t_philo			*philo_id;
}	t_table;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	initialize(t_table *philo);
size_t	get_time_ms(void);
int		go_time(t_philo *philo, size_t time);
void	cleanup_philo(t_table *philo, pthread_t *thread);
int		valid_args(int argc, char *argv[], t_table *philo);
void	print(t_philo *philo, int msg_text);
void	*life_process(void *p);
void	check_die(t_table *philo);

#endif
