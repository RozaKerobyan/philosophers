#include "philo.h"

void	eat_process(t_philo_id *philo)
{
	t_philo	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->fork);
	print(philo, FORK);
	if (table->num_philo == 1)
	{
		go_time(philo, table->time_die);
		print(philo, DIE);
		pthread_mutex_unlock(&philo->fork);
		table->dead = 1;
		return ;
	}
	pthread_mutex_lock(&philo->next->fork);
	print(philo, FORK);
	pthread_mutex_lock(&table->check);
	philo->num_eat++;
	print(philo, EAT);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&table->check);
	go_time(philo, table->time_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*life_process(void *p)
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
		print(philo, SLEEP);
		go_time(philo, table->time_sleep);
		print(philo, THINK);
	}
	return (NULL);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (!philo->dead && ++i < philo->num_philo)
	{
		pthread_mutex_lock(&philo->check);
		if (get_time_ms() - philo->philo_id[i].last_meal
			> (size_t)philo->time_die)
		{
			print(&philo->philo_id[i], DIE);
			philo->dead = 1;
		}
		pthread_mutex_unlock(&philo->check);
		usleep(100);
	}
	return (philo->dead);
}

int	check_full(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->num_eat == -1)
		return (0);
	while (i < philo->num_philo && philo->philo_id[i].num_eat >= philo->num_eat)
		i++;
	if (i == philo->num_philo)
		return (1);
	return (0);
}

void	check_die(t_philo *philo)
{
	while (!philo->full)
	{
		if (check_death(philo))
			break ;
		if (check_full(philo))
			philo->full = 1;
	}
}
