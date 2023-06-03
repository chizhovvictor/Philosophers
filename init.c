/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:17:14 by vchizhov          #+#    #+#             */
/*   Updated: 2023/06/03 17:25:05 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	init_struct_philo(t_info *info, char **av)
{
	int	i;

	i = -1;
	info->number_of_philosophers = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->death = 0;
	info->start_time = timestamp_in_ms();
	if (av[5])
		info->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		info->number_of_times_each_philosopher_must_eat = 0;
	info->philo = malloc(sizeof(t_philo) * info->number_of_philosophers);
	while (++i < info->number_of_philosophers)
	{
		info->philo[i].id = i + 1;
		info->philo[i].left = i;
		info->philo[i].right = i + 1;
		info->philo[i].info = info;
		info->philo[i].count_eat = 0;
		info->philo[i].last_eating = timestamp_in_ms() - info->start_time;
	}
	info->philo[i - 1].right = 0;
	return (1);
}

int	init_struct_mutex(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->wait, NULL))
		return (0);
	if (pthread_mutex_init(&info->check, NULL))
		return (0);
	if (pthread_mutex_init(&info->s_death, NULL))
		return (0);
	info->mutex = malloc(sizeof(pthread_mutex_t) \
			* info->number_of_philosophers);
	if (!info->mutex)
		return (0);
	while (i < info->number_of_philosophers)
	{
		if (pthread_mutex_init(&info->mutex[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print(char *str, t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->info->wait);
	if (philo->info->stop_print != 1)
	{
		printf("%ld %d %s\n", timestamp_in_ms() - \
				philo->info->start_time, id, str);
	}
	pthread_mutex_unlock(&philo->info->wait);
}

int	init_pthread_philo(t_info *info)
{
	int	i;

	i = -1;
	info->stop_print = 0;
	info->all_stop = 0;
	if (pthread_create(&info->check_of_death, \
				NULL, &check_of_death_philo, (void *)info))
		return (0);
	while (++i < info->number_of_philosophers)
	{
		if (pthread_create(&info->philo[i].pthr, \
					NULL, &livephilo, &info->philo[i]))
			return (0);
	}
	if (pthread_join(info->check_of_death, NULL))
		return (0);
	i = -1;
	while (++i < info->number_of_philosophers)
	{
		if (pthread_join(info->philo[i].pthr, NULL))
			return (0);
	}
	return (1);
}

void	mutex_destroy(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->wait);
	pthread_mutex_destroy(&info->check);
	pthread_mutex_destroy(&info->s_death);
	while (i < info->number_of_philosophers)
	{
		pthread_mutex_destroy(&info->mutex[i]);
		i++;
	}
	free(info->mutex);
	free(info->philo);
}
