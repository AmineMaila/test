/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:00:36 by mmaila            #+#    #+#             */
/*   Updated: 2024/03/01 22:37:38 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo_bonus.h"

void	think(t_philo *philo)
{
	print_state("is thinking", philo);
}

void	ft_sleep(t_philo *philo)
{
	print_state("is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->forks);
	print_state("has taken a fork", philo);
	if (philo->philo_count == 1)
	{
		ft_usleep(philo->time_to_die);
		sem_post(philo->forks);
		exit(23);
	}
	sem_wait(philo->forks);
	print_state("has taken a fork", philo);
	sem_wait(philo->meal);
	print_state("is eating", philo);
	philo->last_meal = get_time() - philo->start_time;
	if (++philo->meals_eaten == philo->num_of_meals)
		philo->exit = 1;
	sem_post(philo->meal);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

int	routine(t_philo	*philo)
{
	while (get_time() < philo->delay)
		continue ;
	philo->start_time = get_time();
	if (pthread_create(&philo->eye, NULL, monitor, philo))
		return (1);
	pthread_detach(philo->eye);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat);
	while (1)
	{
		eat(philo);
		if (philo->exit == 1)
			break ;
		ft_sleep(philo);
		think(philo);
	}
	exit(0);
}
