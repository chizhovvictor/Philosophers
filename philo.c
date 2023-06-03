/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:51 by vchizhov          #+#    #+#             */
/*   Updated: 2023/06/03 17:35:03 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	philo_sleep_and_think_print(t_philo *philo)
{
	if (philo->info->death != 1)
	{
		ft_print("is sleeping", philo, philo->id);
		my_sleep(philo->info->time_to_sleep);
		ft_print("is thinking", philo, philo->id);
	}	
}

void	*check_of_death_philo(void *data)
{
	t_info	*info;
	int		i;

	info = (t_info *)data;
	while (info->death != 1)
	{
		i = -1;
		while (++i < info->number_of_philosophers)
		{
			if (info->stop_print != 1)
			{
				pthread_mutex_lock(&info->check);	
				if ((timestamp_in_ms() - info->start_time \
							- info->philo[i].last_eating) > info->time_to_die)
				{
					pthread_mutex_unlock(&info->check);
					ft_print("died", &info->philo[i], info->philo[i].id);
					info->death = 1;
					info->stop_print = 1;
					
					break ;
				}
				pthread_mutex_unlock(&info->check);
			}
		}
		if (info->all_stop)
			break ;
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	int	left;
	int	right;

	if (philo->info->number_of_philosophers == 1)
	{
		my_sleep(philo->info->time_to_die + 100);
		return (0);
	}
	left = philo->left;
	right = philo->right;
	pthread_mutex_lock(&philo->info->mutex[left]);
	pthread_mutex_lock(&philo->info->mutex[right]);
	ft_print("has taken a fork", philo, philo->id);
	ft_print("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->info->check);
	philo->last_eating = timestamp_in_ms() - philo->info->start_time;
	pthread_mutex_unlock(&philo->info->check);
	my_sleep(philo->info->time_to_eat);
	philo->count_eat++;
	pthread_mutex_unlock(&philo->info->mutex[left]);
	pthread_mutex_unlock(&philo->info->mutex[right]);
	return (1);
}

void	*livephilo(void *data)
{
	int		i;
	t_philo	*philo;	

	i = 0;
	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (philo->info->death != 1)
	{
		if (!philo_eat(philo))
			return (NULL);
		if (philo->count_eat == \
				philo->info->number_of_times_each_philosopher_must_eat)
		{
			philo->info->all_stop = 1;
			return (NULL);
		}
		if (philo->info->death != 1)
		{
			philo_sleep_and_think_print(philo);
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac == 5 || ac == 6)
	{
		if (!check_arguments(av))
		{
			printf("Arguments not valided!\n");
			return (1);
		}
		if (!init_struct_philo(&info, av))
			return (1);
		if (!init_struct_mutex(&info))
			return (1);
		if (!init_pthread_philo(&info))
			return (1);
		mutex_destroy(&info);
	}
	else
		printf("Error\n");
	return (0);
}
