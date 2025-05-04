/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yant <yant@student.42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:30:07 by yant              #+#    #+#             */
/*   Updated: 2025/05/05 01:55:39 by yant             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

void	*philo_check(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->count_philo)
		{
			if (get_time() - data->philo[i].last_meal_time > data->time_to_die)
			{
				someone_died(data, i);
				data->end = 1;
				return (NULL);
			}
			if (all_eaten(data))
			{
				data->end = 1;
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	philo_life(t_philo *philo)
{
	while (1)
	{
		if (philo->data->end && philo->data->times_must_eat != -1
			&& philo->times_eaten >= philo->data->times_must_eat)
			break;
		take_forks_end_eat(philo);
		clean_forks(philo);
		philo_sleep(philo);
		if (philo->data->end || all_eaten(philo->data))
			return;
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%lld %d  %s\n", get_time() - philo->data->start_time,
			philo->philo_id + 1, THINK);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}

void	*philo_line(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 1)
		usleep(30);
	philo_life(philo);
	return (NULL);
}

int	ft_init(int argc, char *argv[], t_data *data)
{
	take_values(argc, argv, data);
	data->philo = malloc(sizeof(t_philo) * data->count_philo);
	if (!data->philo)
	{
		printf("Error\n");
		return (free(data), 1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->count_philo);
	if (!data->forks)
	{
		printf("Error\n");
		return (free(data), free(data->philo), 1);
	}
	set_values(data);
	pthread_mutex_init(&data->print_mutex, NULL);
	if (ft_atoi(argv[1]) == 1)
	{
		one_philo(data);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (control_values(argc, argv))
	{
		printf("Error\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("Error");
		return (1);
	}
	if (ft_init(argc, argv, data))
		return (1);
	p_simulator(data);
	clear_malloc(data);
	return (0);
}
