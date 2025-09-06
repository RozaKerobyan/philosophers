/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:47:20 by rkerobya          #+#    #+#             */
/*   Updated: 2025/08/27 19:37:48 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// create for milliseconds

long	get_time_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_die(t_philo *philo)
{
	long	start;

	//start = get_time_ms();
	if (time_to_die)
	{
		start = get_time_ms();
		usleep(time_to_die);
		// here to check case that philo exist and last meal always lower < time_to_die
	}
}



