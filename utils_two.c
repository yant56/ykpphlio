/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yant <yant@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:30:16 by yant              #+#    #+#             */
/*   Updated: 2025/05/18 01:16:05 by yant             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	set_values(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philo[i].philo_id = i;
		data->philo[i].data = data;
		data->philo[i].count_eaten = 0;
		data->philo[i].last_meal_time = get_time();
		i++;
	}
	data->end = 0;
	data->start_time = get_time();
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
		
	pthread_mutex_lock(&philo->data->print_mutex);
	prinf_philo(5,philo->data);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_sleep);
}

void	one_philo(t_data *data)
{
	printf("%lld %d %s\n", get_time() - data->start_time, 1, FORK);// burayı thread ile çalıştır.
	ft_usleep(data->time_to_die);
	printf("%lld %d %s\n", get_time() - data->start_time, 1, DIE);
	clear_malloc(data);
}

void	someone_died(t_data *data, int i)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", get_time() - data->start_time, i + 1, DIE);
	pthread_mutex_unlock(&data->print_mutex);
}
