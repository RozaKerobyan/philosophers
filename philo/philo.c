/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:28:25 by rkerobya          #+#    #+#             */
/*   Updated: 2025/09/09 18:47:10 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(void)
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
