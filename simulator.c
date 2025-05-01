#include "philo.h"

void clean_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->forks[philo->philo_id]);
    pthread_mutex_unlock(&philo->data->forks[(philo->philo_id + 1) % philo->data->count_philo]);
}

void take_forks(t_philo *philo)
{
    int left_fork = philo->philo_id;
    int right_fork = (philo->philo_id + 1) % philo->data->count_philo;

    pthread_mutex_lock(&philo->data->forks[left_fork]);
    pthread_mutex_lock(&philo->data->print_mutex);
   // monitor_print(3, get_time(), philo->philo_id, philo->data);
     printf("%ld %d  %s\n", get_time() - philo->data->start_time,philo->philo_id + 1,FORK);
    pthread_mutex_unlock(&philo->data->print_mutex);
 


    pthread_mutex_lock(&philo->data->forks[right_fork]);
    pthread_mutex_lock(&philo->data->print_mutex);
    //monitor_print(3, get_time(), philo->philo_id, philo->data);
    printf("%ld %d  %s\n", get_time() - philo->data->start_time,philo->philo_id + 1,FORK);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void philo_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
   // monitor_print(4, get_time(), philo->philo_id, philo->data);
    printf("%ld %d  %s\n", get_time() - philo->data->start_time,philo->philo_id + 1,SLEEP);
    pthread_mutex_unlock(&philo->data->print_mutex);

    usleep(philo->data->time_to_sleep * 1000);
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    //monitor_print(5, get_time(), philo->philo_id, philo->data);
     printf("%ld %d  %s\n", get_time() - philo->data->start_time,philo->philo_id + 1,EAT);
    pthread_mutex_unlock(&philo->data->print_mutex);

    philo->last_meal_time = get_time();
    philo->times_eaten++;
    usleep(philo->data->time_to_eat * 1000);
}
int p_simulator(t_data *data)
{
	int i;
	pthread_t t1;

	i = 0;

	if (pthread_create(&t1, NULL, philo_check, data))
	{
		printf("Error\n");
		return (1);
	}
	pthread_detach(t1);
	if (ft_create_threads(data))
		return (1);
	
	if (ft_join_threads(data))
		return (1);
	
	return (0);
}
