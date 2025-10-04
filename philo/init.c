/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:42:25 by rkerobya          #+#    #+#             */
/*   Updated: 2025/09/09 18:42:27 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize(t_table *philo)
{
	int	i;

	philo->full = 0;
	philo->dead = 0;
	philo->philo_id = malloc(philo->num_philo * sizeof(t_philo));
	pthread_mutex_init(&philo->print, NULL);
	pthread_mutex_init(&philo->check, NULL);
	i = 0;
	while (i < philo->num_philo)
	{
		philo->philo_id[i].id = i + 1;
		philo->philo_id[i].table = philo;
		philo->philo_id[i].num_eat = 0;
		if (i + 1 == philo->num_philo)
			philo->philo_id[i].next = &philo->philo_id[0];
		else
			philo->philo_id[i].next = &philo->philo_id[i + 1];
		if (i == 0)
			philo->philo_id[i].before = &philo->philo_id[philo->num_philo - 1];
		else
			philo->philo_id[i].before = &philo->philo_id[i - 1];
		pthread_mutex_init(&philo->philo_id[i].fork, NULL);
		i++;
	}
}
