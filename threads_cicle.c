/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_cicle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:56:21 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/09 13:04:18 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_day_cicle(t_fella *fella)
{
	if (*fella->n_of_fellas > 1
		&& fella->time_while_eating < 0
		&& fella->time_while_sleeping < 0
		&& fella->time_while_thinking < 0
		&& (is_smth(fella->id - 1)
			|| get_ms_diff(fella->sim_start) >= *fella->time_to_eat))
		start_eating(fella);
}

int	increment_hunger(t_fella *fella)
{
	if (fella->time_while_eating < 0
		&& fella->time_while_sleeping < 0)
	{
		pthread_mutex_lock(fella->is_ss);
		if (fella->number_of_meals)
			fella->time_from_last_meal = get_ms_diff(fella->meal_start);
		else
			fella->time_from_last_meal = get_ms_diff(fella->sim_start);
		if (fella->time_from_last_meal >= *fella->time_to_die)
		{
			announce("died", fella, 0);
			*fella->session = 0;
			pthread_mutex_unlock(fella->is_ss);
			return (1);
		}
		pthread_mutex_unlock(fella->is_ss);
	}
	return (0);
}

void	increment_eating_time(t_fella *fella)
{
	if (fella->time_while_eating >= 0)
	{
		fella->time_while_eating = get_ms_diff(fella->meal_start);
		if (fella->time_while_eating >= *fella->time_to_eat)
		{
			fella->time_while_eating = -1;
			pthread_mutex_lock(fella->is_ss);
			fella->number_of_meals += 1;
			pthread_mutex_unlock(fella->is_ss);
			start_sleeping(fella);
			pthread_mutex_unlock(&fella->right_fork);
			pthread_mutex_unlock(fella->left_fork);
		}
	}
}

void	increment_sleeping_time(t_fella *fella)
{
	if (fella->time_while_sleeping >= 0)
	{
		fella->time_while_sleeping = get_ms_diff(fella->sleeping_start);
		if (fella->time_while_sleeping >= *fella->time_to_sleep)
		{
			fella->time_while_sleeping = -1;
			fella->time_from_last_meal = 0;
			start_thinking(fella);
		}
	}
}

void	increment_thinking_time(t_fella *fella)
{
	if (fella->time_while_thinking >= 0)
	{
		fella->time_while_thinking = get_ms_diff(fella->thinking_start);
		if (fella->time_while_thinking
			>= *fella->time_to_eat - *fella->time_to_sleep)
			fella->time_while_thinking = -1;
	}
}
