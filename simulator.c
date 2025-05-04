#include "philo.h"

void clean_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->forks[philo->philo_id]);
    pthread_mutex_unlock(&philo->data->forks[(philo->philo_id + 1) % philo->data->count_philo]);
}

void ft_eat(t_philo *philo)
{
	 pthread_mutex_lock(&philo->data->print_mutex);
     printf("%ld %d  %s\n", get_time() - philo->data->start_time,philo->philo_id + 1,EAT);
    pthread_mutex_unlock(&philo->data->print_mutex);
    philo->last_meal_time = get_time();
    philo->times_eaten++;
    usleep(philo->data->time_to_eat * 1000);
}

void take_forks_end_eat(t_philo *philo)
{
    int left_fork;
    int right_fork;

    left_fork = philo->philo_id;
    right_fork = (philo->philo_id + 1) % philo->data->count_philo;
   
    pthread_mutex_lock(&philo->data->forks[left_fork]);
    if (philo->data->end || all_eaten(philo->data))
		return;
    pthread_mutex_lock(&philo->data->print_mutex);
     printf("%ld %d  %s\n", get_time() - philo->data->start_time,philo->philo_id + 1,FORK);
    pthread_mutex_unlock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->data->forks[right_fork]);
    if (philo->data->end || all_eaten(philo->data))
		return;
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d  %s\n", get_time() - philo->data->start_time,philo->philo_id + 1,FORK);
    pthread_mutex_unlock(&philo->data->print_mutex);
     if (philo->data->end || all_eaten(philo->data))
		return;
    ft_eat(philo);
}

void philo_sleep(t_philo *philo)
{
        if (philo->data->end || all_eaten(philo->data))
		return;
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d  %s\n", get_time() - philo->data->start_time,philo->philo_id + 1,SLEEP);
    pthread_mutex_unlock(&philo->data->print_mutex);
    usleep(philo->data->time_to_sleep * 1000);
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
