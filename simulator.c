/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yant <yant@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:30:14 by yant              #+#    #+#             */
/*   Updated: 2025/05/05 18:53:25 by yant             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void clean_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->forks[philo->philo_id]);
    pthread_mutex_unlock(&philo->data->forks[(philo->philo_id + 1) % philo->data->count_philo]);
}

void ft_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%lld %d %s\n", get_time() - philo->data->start_time,
        philo->philo_id + 1, EAT);
    pthread_mutex_unlock(&philo->data->print_mutex);
    philo->last_meal_time = get_time();
    philo->times_eaten++;
    ft_usleep(philo->data->time_to_eat);
}

void take_forks_end_eat(t_philo *philo)
{
    int left_fork = philo->philo_id;
    int right_fork = (philo->philo_id + 1) % philo->data->count_philo;
    
    // Çatal numaralarını karşılaştırarak sıralama yap
    if (left_fork < right_fork)
    {
        pthread_mutex_lock(&philo->data->forks[left_fork]);
        if (philo->data->end || all_eaten(philo->data))
        {
            pthread_mutex_unlock(&philo->data->forks[left_fork]);
            return;
        }
        
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%lld %d %s\n", get_time() - philo->data->start_time,
               philo->philo_id + 1, FORK);
        pthread_mutex_unlock(&philo->data->print_mutex);
        
        pthread_mutex_lock(&philo->data->forks[right_fork]);
        if (philo->data->end || all_eaten(philo->data))
        {
            pthread_mutex_unlock(&philo->data->forks[left_fork]);
            pthread_mutex_unlock(&philo->data->forks[right_fork]);
            return;
        }
        
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%lld %d %s\n", get_time() - philo->data->start_time,
               philo->philo_id + 1, FORK);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks[right_fork]);
        if (philo->data->end || all_eaten(philo->data))
        {
            pthread_mutex_unlock(&philo->data->forks[right_fork]);
            return;
        }
        
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%lld %d %s\n", get_time() - philo->data->start_time,
               philo->philo_id + 1, FORK);
        pthread_mutex_unlock(&philo->data->print_mutex);
        
        pthread_mutex_lock(&philo->data->forks[left_fork]);
        if (philo->data->end || all_eaten(philo->data))
        {
            pthread_mutex_unlock(&philo->data->forks[right_fork]);
            pthread_mutex_unlock(&philo->data->forks[left_fork]);
            return;
        }
        
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%lld %d %s\n", get_time() - philo->data->start_time,
               philo->philo_id + 1, FORK);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
    
    if (philo->data->end || all_eaten(philo->data))
    {
        clean_forks(philo);
        return;
    }
    
    ft_eat(philo);
    clean_forks(philo); // Yemeği bitirince çatalları bırak
}

void	philo_sleep(t_philo *philo)
{
	if (philo->data->end || all_eaten(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->philo_id + 1, SLEEP);
	pthread_mutex_unlock(&philo->data->print_mutex);
	//usleep(philo->data->time_to_sleep * 1000);
	ft_usleep(philo->data->time_to_sleep);
}

int	p_simulator(t_data *data)
{
	int			i;
	pthread_t	t1;

	i = 0;
	if (pthread_create(&t1, NULL, philo_check, data))
	{
		printf("Error\n");
		return (1);
	}
	//pthread_detach(t1);
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
