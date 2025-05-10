/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yant <yant@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:30:07 by yant              #+#    #+#             */
/*   Updated: 2025/05/10 16:13:21 by yant             ###   ########.fr       */
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
	int		all_ate;
	
	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->count_philo)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (get_time() - data->philo[i].last_meal_time
				> data->time_to_die)
			{
				pthread_mutex_unlock(&data->meal_mutex);
				someone_died(data, i);
				pthread_mutex_lock(&data->end_mutex);
				data->end = 1;
				pthread_mutex_unlock(&data->end_mutex);
				return (NULL);
			}
			
			// all_eaten kontrolünü de mutex içinde yapın
			all_ate = all_eaten(data);
			pthread_mutex_unlock(&data->meal_mutex);
			
			if (all_ate)
			{
				pthread_mutex_lock(&data->end_mutex);
				data->end = 1;
				pthread_mutex_unlock(&data->end_mutex);
				return (NULL);
			}
		}
		ft_usleep(50);
	}
	return (NULL);
}

static void	philo_life(t_philo *philo)
{
    while (1)
    {
        // Yemek sayısını kontrol etmek için meal_mutex kullan
        pthread_mutex_lock(&philo->data->meal_mutex);
        int has_eaten_enough = (philo->data->times_must_eat != -1 && 
                              philo->count_eaten >= philo->data->times_must_eat);
        pthread_mutex_unlock(&philo->data->meal_mutex);
        
        if (has_eaten_enough)
            break;
        
        // End değişkenini kontrol etmek için end_mutex kullan
        pthread_mutex_lock(&philo->data->end_mutex);
        if (philo->data->end)
        {
            pthread_mutex_unlock(&philo->data->end_mutex);
            return;
        }
        pthread_mutex_unlock(&philo->data->end_mutex);
            
        take_forks_end_eat(philo);
        philo_sleep(philo);
        
        pthread_mutex_lock(&philo->data->end_mutex);
        if (philo->data->end)
        {
            pthread_mutex_unlock(&philo->data->end_mutex);
            return;
        }
        pthread_mutex_unlock(&philo->data->end_mutex);
        
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

static int	ft_init(int argc, char *argv[], t_data *data)
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
	pthread_mutex_init(&data->end_mutex, NULL);
	pthread_mutex_init(&data->eaten_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
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
		printf("Error\n");
		return (1);
	}
	if (ft_init(argc, argv, data))
		return (1);
	p_simulator(data);
	clear_malloc(data);
	return (0);
}
