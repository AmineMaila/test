/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:57:02 by mmaila            #+#    #+#             */
/*   Updated: 2024/03/02 15:10:38 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo_bonus.h"

void	init_sem(t_data *data)
{
	sem_unlink("/write");
	data->write = sem_open("/write", O_CREAT | O_EXCL, 0644, 1);
	if (data->write == SEM_FAILED)
		(ft_putstr_fd("sem failed\n", 2), terminate(data), exit(1));
	sem_unlink("/meal");
	data->meal = sem_open("/meal", O_CREAT | O_EXCL, 0644, 1);
	if (data->meal == SEM_FAILED)
		(ft_putstr_fd("sem failed\n", 2), terminate(data), exit(1));
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			data->philo_count);
	if (data->forks == SEM_FAILED)
		(ft_putstr_fd("sem failed\n", 2), terminate(data), exit(1));
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philo[i].id = i + 1;
		data->philo[i].exit = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].delay = data->delay;
		data->philo[i].meals_eaten = 0;
		data->philo[i].num_of_meals = data->num_of_meals;
		data->philo[i].philo_count = data->philo_count;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i].meal = data->meal;
		data->philo[i].forks = data->forks;
		data->philo[i].write = data->write;
		i++;
	}
}

int	check_input(t_data *data)
{
	if (data->num_of_meals > 2147483647
		|| data->time_to_die > 2147483647
		|| data->time_to_eat > 2147483647
		|| data->time_to_sleep > 2147483647)
		return (ft_putstr_fd("invalid input\n", 2), 1);
	return (0);
}

void	init_data(t_data *data)
{
	if (data->argc == 6)
		data->num_of_meals = ft_atoi(data->argv[5]);
	else
		data->num_of_meals = -1;
	data->philo_count = ft_atoi(data->argv[1]);
	data->time_to_die = ft_atoi(data->argv[2]);
	data->time_to_eat = ft_atoi(data->argv[3]);
	data->time_to_sleep = ft_atoi(data->argv[4]);
	data->delay = get_time() + 100;
	if (check_input(data))
		exit(1);
	data->philo = malloc(data->philo_count * sizeof(t_philo));
	if (!data->philo)
		(ft_putstr_fd("allocation failed\n", 2), exit(1));
	data->pids = malloc(data->philo_count * sizeof(int));
	if (!data->pids)
		(free(data->philo), ft_putstr_fd("allocation failed\n", 2), exit(1));
	init_sem(data);
	init_philo(data);
}
