/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:28:25 by rkerobya          #+#    #+#             */
/*   Updated: 2025/10/05 18:29:55 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_program(t_table *table, pthread_t **thread)
{
	int	i;

	*thread = (pthread_t *)malloc(table->num_philo * sizeof(pthread_t));
	if (!*thread)
		return (1);
	table->start_time = get_time_ms();
	i = -1;
	while (++i < table->num_philo)
	{
		if (pthread_create
			(&(*thread)[i], NULL, &life_process, &table->philo_id[i]) != 0)
		{
			write(2, "Error! can't create thread\n", 28);
			free(table->philo_id);
			free(*thread);
			return (1);
		}
		pthread_mutex_lock(&table->check);
		table->philo_id[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->check);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table		table;
	pthread_t	*thread;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error! invalid arguments\n", 26);
		return (1);
	}
	if (valid_args(argc, argv, &table))
		return (1);
	if (start_program(&table, &thread))
		return (1);
	check_die(&table);
	cleanup_philo(&table, thread);
	return (0);
}
