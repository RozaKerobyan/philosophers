/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:28:25 by rkerobya          #+#    #+#             */
/*   Updated: 2025/08/11 19:28:45 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_process(t_philo_id *philo)
{
	t_philo *table;

	table = philo->table;
	pthread_mutex_lock(&philo->fork);
	print(philo, 0);	
	if (table->num_philo == 1)
	{
		go_time(philo, table->time_die);
		print(philo, 4);
		pthread_mutex_unlock(&philo->fork);
		table->dead = 1;
		return ;
	}
	pthread_mutex_lock(&philo->next->fork);
	print(philo, 0);
	pthread_mutex_lock(&table->check);
	philo->num_eat++;
	print(philo, 1);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&table->check);
	go_time(philo, table->time_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*life_process(void	*p)
{
	t_philo		*table;
	t_philo_id	*philo;

	philo = (t_philo_id *)p;
	table = philo->table;
	if (philo->id % 2 == 0)
	{
		usleep(1000);
	}
	while (!table->dead && !table->full)
	{
		eat_process(philo);
		print(philo, 2); 
		go_time(philo, table->time_sleep);
		print(philo, 3); 
	}
	return (NULL);
}

void	check_die(t_philo *philo)
{
	int	i;

	while (!philo->full)
	{
		i = -1;
		while (!philo->dead && ++i < philo->num_philo)
		{
			pthread_mutex_lock(&philo->check);
			if (get_time_ms() - philo->philo_id[i].last_meal > (size_t)philo->time_die)
			{
				print(&philo->philo_id[i], 4);
				philo->dead = 1;
			}
			pthread_mutex_unlock(&philo->check);
			usleep(100);
		}
		if (philo->dead)
			break ;
		i = 0;
		while (philo->num_eat != -1 && i < philo->num_philo && philo->philo_id[i].num_eat >= philo->num_eat)
			i++;
		if (i == philo->num_philo)
			philo->full = 1;
	}
}

static int	error(void)
{
	write(2, "Error! invalid arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_philo		table;
	pthread_t	*thread;

	if ((argc < 5 || argc > 6) || valid_args(argc, argv, &table))
		return (error());
	thread = (pthread_t *)malloc(table.num_philo * sizeof(pthread_t));
	table.start_time = get_time_ms();
	i = -1;
	while (++i < table.num_philo)
	{
		if (pthread_create(&thread[i], NULL, &life_process, &table.philo_id[i]))
		{
			write(2, "Error! cannot create thread\n", 28);
			free(table.philo_id);
			free(thread);
			return (1);
		}
		pthread_mutex_lock(&table.check);
		table.philo_id[i].last_meal = table.start_time;
		pthread_mutex_unlock(&table.check);
	}
	check_die(&table);
	cleanup_philo(&table, thread);
	return (0);
}
