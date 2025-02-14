/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:54:24 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/09 13:06:05 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_non_numeric_args(int argc, char **argv)
{
	int					a;
	int					b;

	a = 1;
	while (a < argc)
	{
		b = 0;
		while (argv[a] && argv[a][b])
		{
			if (argv[a][b] > '9'
					|| argv[a][b] < '0')
				return (0);
			b += 1;
		}
		a += 1;
	}
	return (1);
}

void	get_n_value(char *str, t_lame *num)
{
	int					a;

	a = 0;
	*num = 0;
	while (str && str[a] != '\0')
	{
		*num = (*num * 10) + (str[a] - 48);
		a += 1;
	}
}

int	parse_input(int argc, char **argv, t_fellas *fellas)
{
	if (!check_non_numeric_args(argc, argv))
		return (0);
	fellas->n_times_to_eat = -1;
	get_n_value(argv[1], &fellas->n_of_fellas);
	get_n_value(argv[2], &fellas->time_to_die);
	get_n_value(argv[3], &fellas->time_to_eat);
	get_n_value(argv[4], &fellas->time_to_sleep);
	if (argc == 6)
		get_n_value(argv[5], &fellas->n_times_to_eat);
	fellas->philos = malloc(fellas->n_of_fellas * sizeof(t_fella));
	fellas->session = 1;
	if (!fellas->philos)
		return (0);
	return (1);
}
