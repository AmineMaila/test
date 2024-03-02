/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:28:11 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/28 18:12:17 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/philo_bonus.h"

void	massacre(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
		if (status >> 8 == 23)
		{
			while (i < data->philo_count)
				kill(data->pids[i++], SIGKILL);
			break ;
		}
	}
}

void	exit_sim(t_philo *philo)
{
	sem_wait(philo->write);
	printf("%zu %d died\n",
		get_time() - philo->start_time, philo->id);
	exit(23);
}

void	*monitor(void *pointer)
{
	t_philo	*philo;
	size_t	now;
	int		i;

	philo = (t_philo *)pointer;
	i = 0;
	while (1)
	{
		sem_wait(philo->meal);
		if (philo->exit == 1)
			return (sem_post(philo->meal), NULL);
		now = (get_time()
				- philo->start_time) - philo->last_meal;
		sem_post(philo->meal);
		if (now >= philo->time_to_die)
			return (exit_sim(philo), NULL);
		i = (i + philo->philo_count) % philo->philo_count;
	}
	return (NULL);
}

int	simulate(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (ft_putstr_fd("fork error\n", 2), 0);
		if (data->pids[i] == 0)
			routine(&data->philo[i]);
		i++;
	}
	massacre(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 1;
	while (i < argc)
		if (ft_isdigit(argv[i++]))
			return (ft_putstr_fd("invalid arguments\n", 2), 1);
	if (argc == 5 || argc == 6)
	{
		data.argc = argc;
		data.argv = argv;
		init_data(&data);
		if (data.num_of_meals != 0)
			simulate(&data);
		terminate(&data);
	}
	else
		ft_putstr_fd("insufficent arguments\n", 2);
	return (0);
}
