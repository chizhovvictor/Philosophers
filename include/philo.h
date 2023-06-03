/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchizhov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:35:21 by vchizhov          #+#    #+#             */
/*   Updated: 2023/06/03 17:39:02 by vchizhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_info;

typedef struct s_philo {
	struct s_info	*info;
	pthread_t		pthr;
	int				left;
	int				right;
	int				id;
	long			last_eating;
	int				eat_now;
	long			current_time;
	long			count_eat;

}					t_philo;

typedef struct s_info
{	
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	wait;
	pthread_mutex_t	check;
	pthread_mutex_t	s_death;
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	long			start_time;
	pthread_t		check_of_death;
	int				death;
	int				stop_print;
	int				all_stop;
}					t_info;

long	ft_atoi(const char *str);
int		check_arguments(char **av);
int		check_symbols(char *str);
void	my_sleep(long ms);
long	timestamp_in_ms(void);

int		init_struct_philo(t_info *info, char **av);
int		init_struct_mutex(t_info *info);
void	ft_print(char *str, t_philo *philo, int id);
int		init_pthread_philo(t_info *info);
void	mutex_destroy(t_info *info);

void	philo_sleep_and_think_print(t_philo *philo);
void	*check_of_death_philo(void *data);
int		philo_eat(t_philo *philo);
void	*livephilo(void *data);

#endif
