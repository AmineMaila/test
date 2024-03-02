/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:00:36 by mmaila            #+#    #+#             */
/*   Updated: 2024/03/01 23:27:24 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo.h"

void	think(t_philo *philos)
{
	print_state("is thinking", philos);
}

void	ft_sleep(t_philo *philos)
{
	print_state("is sleeping", philos);
	ft_usleep(philos->time_to_sleep);
}

void	eat(t_philo *philos)
{
	pthread_mutex_lock(philos->fork_l);
	print_state("has taken a fork", philos);
	if (philos->philo_count == 1)
	{
		ft_usleep(philos->time_to_die);
		pthread_mutex_unlock(philos->fork_l);
		return ;
	}
	pthread_mutex_lock(philos->fork_r);
	print_state("has taken a fork", philos);
	pthread_mutex_lock(&philos->meal);
	print_state("is eating", philos);
	philos->last_meal = get_time() - philos->start_time;
	if (++philos->meals_eaten == philos->num_of_meals)
		philos->exit = 1;
	pthread_mutex_unlock(&philos->meal);
	ft_usleep(philos->time_to_eat);
	pthread_mutex_unlock(philos->fork_l);
	pthread_mutex_unlock(philos->fork_r);
}

int	philo_dead(t_philo *philos)
{
	pthread_mutex_lock(philos->death);
	if (*philos->dead == 1)
		return (pthread_mutex_unlock(philos->death), 1);
	pthread_mutex_unlock(philos->death);
	return (0);
}

void	*routine(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	pthread_mutex_lock(&philos->time);
	philos->start_time = get_time();
	pthread_mutex_unlock(&philos->time);
	if (philos->id % 2 == 0)
		ft_usleep(philos->time_to_eat);
	while (!philo_dead(philos))
	{
		eat(philos);
		if (philos->exit == 1)
			return (NULL);
		ft_sleep(philos);
		think(philos);
	}
	return (NULL);
}
