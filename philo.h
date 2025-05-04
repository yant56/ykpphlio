/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yant <yant@student.42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:30:11 by yant              #+#    #+#             */
/*   Updated: 2025/05/05 02:32:27 by yant             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIE "died"

typedef struct s_philo
{
	int				philo_id;
	int				times_eaten;
	long			last_meal_time;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long long		start_time;
	int				count_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
}	t_data;

int			control_values(int argc, char **argv);
int			ft_atoi(char *str);
void		set_values(t_data *data);
void		clear_malloc(t_data *data);
void		one_philo(t_data *data);
void		clean_forks(t_philo *philo);
void		take_forks_end_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
int			all_eaten(t_data *data);
long long	get_time(void);
int			p_simulator(t_data *data);
void		someone_died(t_data *data, int i);
int			ft_create_threads(t_data *data);
int			ft_join_threads(t_data *data);
void		take_values(int argc, char **argv, t_data *data);
void		*philo_line(void *arg);
void		*philo_check(void *arg);

#endif
