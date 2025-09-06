#include "philo.h"

void	initialize(t_philo *philo)
{
	int	i;

	i = 0;
	philo->full = 0;
	philo->dead = 0;
	philo->philo_id = malloc(philo->num_philo * sizeof(t_philo));
	while (i < philo->num_count)
	{
		philo->philo_id[i].id = i + 1;
		philo->philo_id[i].table = table;
		philo->philo_id[i].num_eat = 0;
		if (i + 1 == philo->num_count)
			philo->philo_id[i].next = &philo->philo_id[0];
		else
			philo->philo_id[i].next = &philo->philo_id[i + 1];
		if (i == 0)
			philo->philo_id[i].before = &philo->philo_id[philo->num_philo - 1];
		else
			philo->philo_id[i].before = &philo->philo_id[i - 1];
		pthread_mutex_init(&philo->print, NULL);
		pthread_mutex_init(&philo->check, NULL);
		i++;
	}
}
