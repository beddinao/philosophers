/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_cicle_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:55:38 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/09 13:04:36 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_eating(t_fella *fella)
{
	fella->time_while_eating = 0;
	pthread_mutex_lock(&fella->right_fork);
	announce("has taken a fork", fella, 1);
	pthread_mutex_lock(fella->left_fork);
	announce("has taken a fork", fella, 1);
	gettimeofday(&fella->meal_start, NULL);
	announce("is eating", fella, 1);
}

void	start_sleeping(t_fella *fella)
{
	fella->time_while_sleeping = 0;
	gettimeofday(&fella->sleeping_start, NULL);
	announce("is sleeping", fella, 1);
}

void	start_thinking(t_fella *fella)
{
	fella->time_while_thinking = 0;
	gettimeofday(&fella->thinking_start, NULL);
	announce("is thinking", fella, 1);
}
