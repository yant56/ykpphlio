#include "philo.h"

int ft_create_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->count_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philo_line,
						   &data->philo[i]))
		{
			printf("Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int ft_join_threads(t_data *data)
{
	int i;

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

int ft_atoi(const char *str)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	else if (str[i] == '+')
		i++;

	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long get_time(void)
{
	static struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

int all_eaten(t_data *data)
{
	int i = 0;

	while (i < data->count_philo)
	{
		if (data->times_must_eat == -1)
			return (0);
		else if (data->times_must_eat > 0)
		{
			if (data->philo[i].times_eaten < data->times_must_eat)
				return (0);
		}
		i++;
	}
	return (1);
}
