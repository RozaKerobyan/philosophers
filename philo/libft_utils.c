/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:33:16 by rkerobya          #+#    #+#             */
/*   Updated: 2025/09/01 14:21:03 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_atoi(const char *str)
{
        int                                     i;
        int                                     sign;
        unsigned long int       result;

        i = 0;
        sign = 1;
        result = 0;
        while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
                i++;
        if (str[i] == '+')
                i++;
        else if (str[i] == '-')
        {
                sign = -1;
                i++;
        }
        while (ft_isdigit(str[i]))
        {
                result = result * 10 + (str[i] - 48);
                i++;
        }
        return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
