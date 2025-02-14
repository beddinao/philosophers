/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:55:22 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/09 13:01:27 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

typedef long long	t_lame;

typedef struct philosopher
{
	int						id;
	pthread_t				thread;
	pthread_mutex_t			right_fork;
	pthread_mutex_t			*left_fork;
	t_lame					time_from_last_meal;
	t_lame					time_while_sleeping;
	t_lame					time_while_eating;
	t_lame					time_while_thinking;
	struct timeval			meal_start;
	struct timeval			sleeping_start;
	struct timeval			thinking_start;
	struct timeval			sim_start;
	t_lame					*n_of_fellas;
	t_lame					*time_to_die;
	t_lame					*time_to_sleep;
	t_lame					*time_to_eat;
	int						number_of_meals;
	pthread_mutex_t			*is_ss;
	int						*session;
}		t_fella;

typedef struct admin
{
	t_lame					id;
	pthread_t				job;
}		t_admin;

typedef struct philosophers
{
	t_lame					n_of_fellas;
	t_lame					time_to_die;
	t_lame					time_to_eat;
	t_lame					time_to_sleep;
	t_lame					n_times_to_eat;
	t_fella					*philos;
	pthread_mutex_t			is_ss;
	int						session;
}			t_fellas;

t_lame			get_ms_diff(struct timeval time);

void			get_n_value(char *str, t_lame *num);
void			__delete_traces(t_fellas *fellas);
void			increment_thinking_time(t_fella *fella);
void			increment_sleeping_time(t_fella *fella);
void			increment_eating_time(t_fella *fella);
void			philosopher_day_cicle(t_fella *fella);
void			start_thinking(t_fella *fella);
void			start_sleeping(t_fella *fella);
void			start_eating(t_fella *fella);
void			announce(char *what, t_fella *fella, int c);

int				is_smth(t_lame number);
int				parse_input(int argc, char **argv, t_fellas *fellas);
int				increment_hunger(t_fella *fella);
int				check_non_numeric_args(int argc, char **argv);
int				check_fellas_fulfillment(t_fellas *fellas, int a);

#endif
