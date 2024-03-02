/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:57:02 by mmaila            #+#    #+#             */
/*   Updated: 2024/03/02 22:57:03 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo.h"

void	init_mutexes(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].meal, NULL);
		pthread_mutex_init(&data->philos[i].time, NULL);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
}

void	init_philos(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].fork_l = &data->forks[i];
		if (i != data->philo_count - 1)
			data->philos[i].fork_r = &data->forks[i + 1];
		else
			data->philos[i].fork_r = &data->forks[0];
		data->philos[i].num_of_meals = -2;
		data->philos[i].last_meal = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].exit = 0;
		data->philos[i].philo_count = data->philo_count;
		data->philos[i].dead = &data->dead;
		data->philos[i].id = i + 1;
		data->philos[i].write_lock = &data->write;
		data->philos[i].death = &data->death_lock;
		if (data->argc == 6)
			data->philos[i].num_of_meals = ft_atoi(data->argv[5]);
		data->philos[i].time_to_die = ft_atoi(data->argv[2]);
		data->philos[i].time_to_eat = ft_atoi(data->argv[3]);
		data->philos[i++].time_to_sleep = ft_atoi(data->argv[4]);
	}
}

int	check_input(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (data->philos[i].num_of_meals > 2147483647
			|| data->philos[i].time_to_die > 2147483647
			|| data->philos[i].time_to_eat > 2147483647
			|| data->philos[i].time_to_sleep > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_rules *data)
{
	data->exited = 0;
	data->dead = 0;
	data->philo_count = ft_atoi(data->argv[1]);
	data->philos = malloc(data->philo_count * sizeof(t_philo));
	if (!data->philos)
		return (ft_putstr_fd("allocation failed\n", 2), 1);
	data->forks = malloc(data->philo_count * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (free(data->philos), ft_putstr_fd("allocation failed\n", 2), 1);
	init_mutexes(data);
	init_philos(data);
	if (check_input(data))
		return (terminate(data), ft_putstr_fd("invalid input\n", 2), 1);
	return (0);
}
