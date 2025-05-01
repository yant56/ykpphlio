
#include "philo.h"

void *philo_check(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->count_philo)
		{
			if (get_time() - data->philo[i].last_meal_time > data->time_to_die)
			{
				someone_died(data, i);// eğer birisi öldüyse
				return (NULL);
			}
			if (all_eaten(data)) // Eğer tüm filozoflar yemeğini yediyse
			{
				data->end = 1;
				return (NULL);
			}
		}

	}
	return (NULL);
}


void philo_life(t_philo *philo)
{
	
	while (1)
	{
		if (philo->data->end)
			break;

		if (philo->data->times_must_eat != -1 && philo->times_eaten >= philo->data->times_must_eat)
		{
			philo->finished = 1;
			break;
		}
	
		take_forks(philo);
		eat(philo);
		clean_forks(philo);
		philo_sleep(philo);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d  %s\n", get_time() - philo->data->start_time,philo->philo_id + 1,THINK);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}


}


void *philo_line(void *arg)
{
	t_philo *philo;
	//pthread_t t1;

	philo = (t_philo *)arg;


    if (philo->philo_id % 2 == 1)
	{
		 usleep(30);

		 if(philo->data->count_philo % 2 == 1)
		 {
			 if(philo->philo_id == philo->data->count_philo - 1)
			 {
				 usleep(100);
			 }
		 }
	}
       philo_life(philo);

	return(NULL);
}





int ft_init(int argc, char *argv[], t_data *data)
{
	take_values(argc,argv,data);// değerleride aldık buda oke.
	data->philo = malloc(sizeof(t_philo) * data->count_philo);
	if (!data->philo)
	{
		printf("Error\n");
		return (free(data),1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->count_philo);
	if (!data->forks)
	{
		printf("Error\n");
		return (free(data),1);
	}
	set_values(data);// philo değerlerini gir.
	
	pthread_mutex_init(&data->print_mutex, NULL);
	
	if (ft_atoi(argv[1]) == 1)
	{
		one_philo(data);
		return (1);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_data *data;
	
	if (control_values(argc, argv)) // kontrol kısımı oke.
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
		// yarın baktığım zaman tek sayıda philo ce cift sayıda philo için kod yaz.
	
	p_simulator(data);
	clear_malloc(data);

	return (0);
}
