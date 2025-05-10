/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yant <yant@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:30:20 by yant              #+#    #+#             */
/*   Updated: 2025/05/10 04:18:05 by yant             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_philo)
	{
		if (pthread_create(&data->philo[i].thread,
				NULL, philo_line, &data->philo[i]))
		{
			printf("Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
		{
			printf("Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	all_eaten(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_philo)
	{
		if (data->times_must_eat == -1)
			return (0);
		else if (data->times_must_eat > 0)
		{
			if (data->philo[i].count_eaten < data->times_must_eat)
				return (0);
		}
		i++;
	}
	return (1);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time() + time;
	while (get_time() <= start)
		usleep(500);
}
