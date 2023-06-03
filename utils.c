/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:53:23 by vchizhov          #+#    #+#             */
/*   Updated: 2023/06/03 17:10:46 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

long	ft_atoi(const char *str)
{
	long	res;
	long	sign;
	long	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

long	timestamp_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_symbols(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			check++;
		i++;
	}
	return (check);
}	

int	check_arguments(char **av)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	while (av[i])
	{
		check += check_symbols(av[i]);
		i++;
	}
	if (check)
		return (0);
	if (av[5])
		if (ft_atoi(av[5]) == 0)
			return (0);
	if (av[1])
		if (ft_atoi(av[1]) == 0)
			return (0);
	return (1);
}

void	my_sleep(long ms)
{
	long	t;

	t = timestamp_in_ms();
	while (timestamp_in_ms() - t < ms)
		usleep(1);
}
