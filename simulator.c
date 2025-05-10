/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yant <yant@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:30:14 by yant              #+#    #+#             */
/*   Updated: 2025/05/10 15:36:42 by yant             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->philo_id + 1, EAT);
	pthread_mutex_unlock(&philo->data->print_mutex);
	
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->count_eaten++; // Bu satırı meal_mutex koruması altına aldım
	pthread_mutex_unlock(&philo->data->meal_mutex);
	
	ft_usleep(philo->data->time_to_eat);
}

static int	ft_left_fork(int right_fork, int left_fork, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	
	// end değişkenine erişim için mutex kullan
	pthread_mutex_lock(&philo->data->end_mutex);
	int should_end = philo->data->end;
	pthread_mutex_unlock(&philo->data->end_mutex);
	
	if (should_end)
	{
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		return (1);
	}
	
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->philo_id + 1, FORK);
	pthread_mutex_unlock(&philo->data->print_mutex);
	
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	
	// İkinci end kontrolü için de mutex kullan
	pthread_mutex_lock(&philo->data->end_mutex);
	should_end = philo->data->end;
	pthread_mutex_unlock(&philo->data->end_mutex);
	
	if (should_end)
	{
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		return (1);
	}
	
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->philo_id + 1, FORK);
	pthread_mutex_unlock(&philo->data->print_mutex);
	
	return (0);
}

static int	ft_right_fork(int right_fork, int left_fork, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->philo_id + 1, FORK);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->philo_id + 1, FORK);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

void	take_forks_end_eat(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->philo_id;
	right_fork = (philo->philo_id + 1) % philo->data->count_philo;
	if (left_fork < right_fork)
	{
		if (ft_left_fork(right_fork, left_fork, philo))
			return ;
	}
	else
	{
		if (ft_right_fork(right_fork, left_fork, philo))
			return ;
	}
	if (philo->data->end)
	{
		clean_forks(philo);
		return ;
	}
	ft_eat(philo);
	clean_forks(philo);
}

int	p_simulator(t_data *data)
{

	pthread_t	t1;

	data->start_time = get_time();
	if (pthread_create(&t1, NULL, philo_check, data))
	{
		printf("Error\n");
		return (1);
	}
	if (ft_create_threads(data))
		return (1);
	if (ft_join_threads(data))
		return (1);
	if (pthread_join(t1, NULL))
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}
