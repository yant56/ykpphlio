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
		data->philo[i].finished = 0;
		i++;
	}
	data->end = 0;
	data->start_time = get_time();
	//pthread_mutex_init(data->print_mutex, NULL);
}

void monitor_print(int flag, long time, int philo_id, t_data *data)
{
	if (data->end || all_eaten(data))
		return;
	if (flag == 1)
	{
		printf("%ld %d  %s\n", time - data->start_time,
			   philo_id + 1,DIE);
	}
	else if (flag == 2)
	{
		printf("%ld %d %s\n", time - data->start_time, philo_id + 1,THINK);
	}
	else if (flag == 3)
	{
		printf("%ld %d  %s\n", time - data->start_time, philo_id + 1,FORK);
	}
	else if (flag == 4)
	{
		printf("%ld %d %s\n", time - data->start_time, philo_id + 1,SLEEP);
	}
	else if (flag == 5)
	{
		printf("%ld %d  %s\n", time - data->start_time, philo_id + 1,EAT);
	}
}

void clear_malloc(t_data *data)
{
	int i;

	i = 0;
	while (i < data->count_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data)
	{
		free(data);
		data = NULL;
	}
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
	//monitor_print(1, get_time(), i, data);
	printf("%ld %d  %s\n", get_time() - data->start_time,data->philo->philo_id + 1,DIE);
	data->end = 1;
	pthread_mutex_unlock(&data->print_mutex);
}