/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:02:28 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/28 16:42:14 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo_bonus.h"

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
	while (get_time() - start != sleep)
		usleep(100);
}

void	print_state(char *msg, t_philo *philo)
{
	size_t	timestamp;

	sem_wait(philo->write);
	timestamp = get_time() - philo->start_time;
	printf("%zu %d %s\n", timestamp, philo->id, msg);
	sem_post(philo->write);
}

void	terminate(t_data *data)
{
	free(data->philo);
	free(data->pids);
	sem_close(data->forks);
	sem_close(data->meal);
	sem_close(data->write);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/meal");
}
