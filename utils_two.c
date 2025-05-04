#include "philo.h"

void set_values(t_data *data)
{
	int i;

	i = 0;
	while (i < data->count_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philo[i].philo_id = i;
		data->philo[i].data = data;
		data->philo[i].times_eaten = 0;
		data->philo[i].last_meal_time = get_time();
		i++;
	}
	data->end = 0;
	data->start_time = get_time();
}



void clear_malloc(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->count_philo)
		pthread_mutex_destroy(&data->forks[i]);
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	if (data)
		free(data);
}

void one_philo(t_data *data)
{
	printf("%ld %d has taken a fork\n", get_time() - data->start_time, 1);
	usleep(data->time_to_die * 1000);
	printf("%ld %d died\n", get_time() - data->start_time, 1);
	clear_malloc(data);
}

void someone_died(t_data *data, int i)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d  %s\n", get_time() - data->start_time, i + 1, DIE);
	pthread_mutex_unlock(&data->print_mutex);
}