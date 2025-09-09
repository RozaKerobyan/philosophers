/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:08:19 by rkerobya          #+#    #+#             */
/*   Updated: 2025/09/01 14:48:00 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(char *s)
{
	long	num;
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
		return (0);
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	num = ft_atoi(s);
	if (num > 2147483647)
		return (0);
	return (1);
}

int	valid_args(int argc, char *argv[], t_philo *philo)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_num(argv[i]))
			return (1);
		i++;
	}
	philo->num_philo = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->num_eat = -1;
	if (argc == 6)
		philo->num_eat = ft_atoi(argv[5]);
	initialize(philo);
	return (0);
}

