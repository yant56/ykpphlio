/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yant <yant@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:30:11 by yant              #+#    #+#             */
/*   Updated: 2025/05/10 04:22:17 by yant             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	clear_malloc(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->count_philo)
		pthread_mutex_destroy(&data->forks[i]);
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
		pthread_mutex_destroy(&data->print_mutex);
	if (data)
		free(data);
}

void	clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->philo_id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->philo_id + 1)
		% philo->data->count_philo]);
}
