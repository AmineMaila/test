/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:02:28 by mmaila            #+#    #+#             */
/*   Updated: 2024/03/02 23:09:36 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo.h"

size_t	get_time(void)
{
	size_t			return_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	return_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (return_time);
}

void	ft_usleep(size_t sleep)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < sleep)
		usleep(100);
}

size_t	time_passed(t_philo *philo)
{
	size_t	since;

	pthread_mutex_lock(&philo->time);
	since = get_time() - philo->start_time;
	pthread_mutex_unlock(&philo->time);
	return (since);
}

void	print_state(char *msg, t_philo *philos)
{
	size_t	timestamp;

	if (philo_dead(philos))
		return ;
	pthread_mutex_lock(philos->write_lock);
	timestamp = get_time() - philos->start_time;
	printf("%zu %d %s\n", timestamp, philos->id, msg);
	pthread_mutex_unlock(philos->write_lock);
}

void	terminate(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].time);
		pthread_mutex_destroy(&data->philos[i].meal);
		i++;
	}
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->write);
	free(data->forks);
	free(data->philos);
}
