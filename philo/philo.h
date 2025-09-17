/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:19:10 by rkerobya          #+#    #+#             */
/*   Updated: 2025/09/09 19:00:22 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo_id
{
	int			id;
	int			num_eat;
	size_t			last_meal;
	//pthread_mutex_t		fork;
	struct s_philo_id	*before;
	struct s_philo_id	*next;
	struct s_philo		*table;
}	t_philo_id;

typedef struct s_philo
{
	int		num_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		num_eat;
	int		dead;
	int		full;
	size_t		start_time;
	//pthread_mutex_t	check;
	//pthread_mutex_t	print;
	t_philo_id	*philo_id;
}	t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	initialize(t_philo *philo);
size_t	get_time_ms(void);
int		go_time(t_philo_id *philo, size_t time);
void	cleanup_philo(t_philo *philo, pthread_t *thread);
int		valid_args(int argc, char *argv[], t_philo *philo);
void	print(t_philo_id *philo, int msg_id);

#endif
