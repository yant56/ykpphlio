#include "philo.h"

static int check_digit(int argc,char **argv)
{
	int i = 1;
	int j = 0;
    while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return 1;
			j++;
		}
		i++;	
	}
	
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return 1;
	return 0;
}

 void take_values(int argc,char **argv, t_data *data)

{
	data->count_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->times_must_eat = -1;
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
}

int control_values(int argc , char **argv)
{
    int i;
	
	i = 0;
	if (argc < 5 || argc > 6)
		return 1;
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return 1;
	if (check_digit(argc,argv))
		return 1;
	return 0;

}