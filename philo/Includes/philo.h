/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:17:04 by mmaila            #+#    #+#             */
/*   Updated: 2024/03/02 22:54:11 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*death;
	pthread_mutex_t	meal;
	pthread_mutex_t	time;
	int				*dead;
	int				exit;
	int				id;
	int				philo_count;
	int				num_of_meals;
	int				meals_eaten;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			last_meal;
}			t_philo;

typedef struct s_rules
{
	t_philo			*philos;
	pthread_t		eye;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	write;
	char			**argv;
	int				argc;
	int				philo_count;
	int				exited;
	int				dead;
}			t_rules;

int		ft_atoi(const char *str);
int		ft_isdigit(char *str);
int		init_data(t_rules *data);
int		philo_dead(t_philo *philos);
void	init_mutexes(t_rules *data);
void	init_philos(t_rules *data);
void	ft_putstr_fd(char *str, int fd);
void	*routine(void *pointer);
void	ft_usleep(size_t sleep);
void	print_state(char *msg, t_philo *philos);
void	terminate(t_rules *data);
size_t	time_passed(t_philo *philo);
size_t	get_time(void);


#endif