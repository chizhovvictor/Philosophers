/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:51 by vchizhov          #+#    #+#             */
/*   Updated: 2023/06/27 18:09:10 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	func_for_death(t_info *info)
{
	int	i;

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
				pthread_mutex_lock(&info->m_death);
				info->death = 1;
				pthread_mutex_unlock(&info->m_death);
				pthread_mutex_lock(&info->m_stop_print);
				info->stop_print = 1;
				pthread_mutex_unlock(&info->m_stop_print);
				break ;
			}
			pthread_mutex_unlock(&info->check);
		}
	}
}

void	check_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_stop_print);
	if (philo->info->death != 1)
	{
		pthread_mutex_unlock(&philo->info->m_stop_print);
		philo_sleep_and_think_print(philo);
	}
	pthread_mutex_unlock(&philo->info->m_stop_print);
}
