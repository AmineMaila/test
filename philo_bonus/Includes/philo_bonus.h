/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:17:04 by mmaila            #+#    #+#             */
/*   Updated: 2024/03/02 14:52:59 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo
{
	pthread_t	eye;
	sem_t		*forks;
	sem_t		*write;
	sem_t		*meal;
	int			id;
	int			exit;
	int			philo_count;
	int			num_of_meals;
	int			meals_eaten;
	size_t		delay;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		start_time;
	size_t		last_meal;
}			t_philo;

typedef struct s_data
{
	t_philo		*philo;
	sem_t		*forks;
	sem_t		*write;
	sem_t		*meal;
	char		**argv;
	int			argc;
	int			*pids;
	int			philo_count;
	int			num_of_meals;
	size_t		delay;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		start_time;
}			t_data;

void	terminate(t_data *data);
void	init_data(t_data *data);
void	*monitor(void *pointer);
int		ft_atoi(const char *str);
int		ft_isdigit(char *str);
void	ft_putstr_fd(char *str, int fd);
int		routine(t_philo	*philo);
void	ft_usleep(size_t sleep);
void	print_state(char *msg, t_philo *philo);
size_t	get_time(void);

#endif