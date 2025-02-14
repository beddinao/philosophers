/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:53:03 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/09 13:05:46 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	__begin_life(t_fella *fella)
{
	gettimeofday(&fella->sim_start, NULL);
	while (1)
	{
		philosopher_day_cicle(fella);
		increment_eating_time(fella);
		increment_sleeping_time(fella);
		increment_thinking_time(fella);
		if (increment_hunger(fella))
			break ;
	}
}

void	*f_routine(void *arg)
{
	t_fella			*fella;

	fella = (t_fella *)arg;
	fella->number_of_meals = 0;
	fella->time_from_last_meal = 0;
	fella->time_while_eating = -1;
	fella->time_while_sleeping = -1;
	fella->time_while_thinking = -1;
	pthread_mutex_init(&fella->right_fork, NULL);
	__begin_life(fella);
	return (NULL);
}

void	*__monitor(void *arg)
{
	t_fellas		*fellas;

	fellas = (t_fellas *)arg;
	while (1)
	{
		pthread_mutex_lock(&fellas->is_ss);
		if (!fellas->session
			|| check_fellas_fulfillment(fellas, 0))
			break ;
		pthread_mutex_unlock(&fellas->is_ss);
	}
	fellas->session = 0;
	pthread_mutex_unlock(&fellas->is_ss);
	usleep(fellas->n_of_fellas * 1000);
	__delete_traces(fellas);
	return (NULL);
}

void	__create(t_fellas *fellas, t_admin *admin)
{
	int						a;
	int						b;

	a = 0;
	while (a < fellas->n_of_fellas)
	{
		b = a + 1;
		if (b >= fellas->n_of_fellas)
			b = 0;
		fellas->philos[a].id = a + 1;
		fellas->philos[a].left_fork = &fellas->philos[b].right_fork;
		fellas->philos[a].time_to_die = &fellas->time_to_die;
		fellas->philos[a].time_to_sleep = &fellas->time_to_sleep;
		fellas->philos[a].time_to_eat = &fellas->time_to_eat;
		fellas->philos[a].n_of_fellas = &fellas->n_of_fellas;
		fellas->philos[a].is_ss = &fellas->is_ss;
		fellas->philos[a].session = &fellas->session;
		pthread_create(&fellas->philos[a].thread, NULL,
			f_routine, &fellas->philos[a]);
		a += 1;
	}
	pthread_create(&admin->job, NULL, __monitor, fellas);
	pthread_join(admin->job, NULL);
	pthread_detach(admin->job);
}

int	main(int argc, char **argv)
{
	t_fellas				fellas;
	t_admin					admin;

	admin.id = 0;
	if (argc == 5 || argc == 6)
	{
		if (!parse_input(argc, argv, &fellas))
			return (1);
		pthread_mutex_init(&fellas.is_ss, NULL);
		__create(&fellas, &admin);
	}
	return (0);
}
