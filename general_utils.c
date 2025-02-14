/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:52:09 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/09 13:02:42 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_lame	get_ms_diff(struct timeval time)
{
	struct timeval	time_now;
	t_lame			diff;

	gettimeofday(&time_now, NULL);
	diff = ((time_now.tv_sec - time.tv_sec) * 1000)
		+ ((time_now.tv_usec - time.tv_usec) / 1000);
	return (diff);
}

void	announce(char *what, t_fella *fella, int c)
{
	if (c)
		pthread_mutex_lock(fella->is_ss);
	if (!c || *fella->session)
		printf("%lli  %i  %s\n",
			get_ms_diff(fella->sim_start), fella->id, what);
	if (c)
		pthread_mutex_unlock(fella->is_ss);
}

int	is_smth(t_lame number)
{
	while (number > 1)
		number -= 2;
	if (!number)
		return (1);
	return (0);
}

void	__delete_traces(t_fellas *fellas)
{
	int				a;

	a = 0;
	while (a < fellas->n_of_fellas)
	{
		pthread_detach(fellas->philos[a].thread);
		pthread_mutex_destroy(&fellas->philos[a].right_fork);
		a += 1;
	}
	pthread_mutex_destroy(&fellas->is_ss);
	free(fellas->philos);
}

int	check_fellas_fulfillment(t_fellas *fellas, int a)
{
	int					fellas_fulfilled;

	fellas_fulfilled = 0;
	if (fellas->n_times_to_eat > 0)
	{
		while (fellas->session && a < fellas->n_of_fellas)
		{
			if (fellas->philos[a].number_of_meals
				>= fellas->n_times_to_eat)
				fellas_fulfilled += 1;
			a += 1;
		}
	}
	if (!fellas->session
		|| fellas_fulfilled == fellas->n_of_fellas)
		return (1);
	return (0);
}
