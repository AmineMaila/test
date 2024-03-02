/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:28:11 by mmaila            #+#    #+#             */
/*   Updated: 2024/03/02 00:10:08 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo.h"

int	exit_sim(t_philo *philo, t_rules *data)
{
	if (philo->exit == 0)
	{
		pthread_mutex_lock(&data->death_lock);
		data->dead = 1;
		pthread_mutex_unlock(&data->death_lock);
		pthread_mutex_lock(&philo->time);
		printf("%zu %d died\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(&philo->time);
		return (1);
	}
	data->exited++;
	return (0);
}

void	*monitor(void *pointer)
{
	t_rules	*data;
	size_t	now;
	int		i;

	data = (t_rules *)pointer;
	ft_usleep(data->philos->time_to_die / 2);
	i = 0;
	while (data->exited != data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].meal);
		now = time_passed(&data->philos[i]);
		if (now - data->philos[i].last_meal >= data->philos[i].time_to_die)
			if (exit_sim(&data->philos[i], data))
				return (pthread_mutex_unlock(&data->philos[i].meal), NULL);
		pthread_mutex_unlock(&data->philos[i++].meal);
		i = (i + data->philo_count) % data->philo_count;
	}
	return (NULL);
}

int	simulate(t_rules *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->eye, NULL, monitor, data))
		return (ft_putstr_fd("Create error\n", 2), 0);
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, routine, &data->philos[i]))
			return (ft_putstr_fd("Create error\n", 2), 0);
		i++;
	}
	if (pthread_join(data->eye, NULL))
		return (ft_putstr_fd("join error\n", 2), 0);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (ft_putstr_fd("join error\n", 2), 0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules	data;
	int		i;

	i = 1;
	while (i < argc)
		if (ft_isdigit(argv[i++]))
			return (ft_putstr_fd("invalid arguments\n", 2), 1);
	if (argc == 5 || argc == 6)
	{
		data.argc = argc;
		data.argv = argv;
		if (init_data(&data))
			return (1);
		if (data.philos->num_of_meals != 0)
			simulate(&data);
		terminate(&data);
	}
	else
		ft_putstr_fd("insufficent arguments\n", 2);
	return (0);
}
