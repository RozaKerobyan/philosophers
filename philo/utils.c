/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:47:20 by rkerobya          #+#    #+#             */
/*   Updated: 2025/09/09 18:52:14 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	go_time(t_philo_id *philo, size_t time)
{
	size_t	start;

	start = get_time_ms();
	while (!philo->table->dead)
	{
		if (get_time_ms() - start >= time)
		{
			break ;
		}
		usleep(100);
	}
	return (0);
}

void	cleanup_philo(t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_destroy(&philo->philo_id[i].fork);
		i++;
	}
	pthread_mutex_destroy(&philo->print);
	pthread_mutex_destroy(&philo->check);
	free(philo->philo_id);
	free(thread);
}

char	*msg(int msg_id)
{
	if (msg_id == 0)
		return ("has taken a fork");
	if (msg_id == 1)
		return ("is eating");
	if (msg_id == 2)
		return ("is sleeping");
	if (msg_id == 3)
		return ("is thinking");
	if (msg_id == 4)
		return ("died");
	return ("Error: invalid message id");
}

void	print(t_philo_id *philo, int msg_id)
{
	size_t	time;

	time = get_time_ms() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->print);
	if (!philo->table->dead && !philo->table->full)
	{
		printf("%ld ", time);
		printf("%d ", philo->id);
		printf("%s\n", msg(msg_id));
	}
	pthread_mutex_unlock(&philo->table->print);
}
