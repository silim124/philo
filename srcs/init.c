/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:23:14 by silim             #+#    #+#             */
/*   Updated: 2021/12/19 00:47:03 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_game *game)
{
	int	i;

	if (pthread_mutex_init(&(game->m_print), NULL)
		|| pthread_mutex_init(&(game->m_eating), NULL))
		return (0);
	game->m_fork = malloc(sizeof(pthread_mutex_t) * game->philo_num);
	if (!(game->m_fork))
		return (0);
	i = 0;
	while (i < game->philo_num)
	{
		if (pthread_mutex_init(&(game->m_fork[i]), NULL))
			return (0);
		i++;
	}
	return (1);
}

int	init_philo(t_game *game)
{
	int	i;

	i = 0;
	game->philo = malloc(sizeof(t_game) * game->philo_num);
	if (!(game->philo))
		return (0);
	while (i < game->philo_num)
	{
		game->philo[i].id = i;
		game->philo[i].left_fork_id = i;
		game->philo[i].right_fork_id = (i + 1) % game->philo_num;
		game->philo[i].last_eat_time = 0;
		game->philo[i].eat_num = 0;
		game->philo[i].game = game;
		i++;
	}
	return (1);
}

int	init_game(t_game *game, int	input_num, char **input)
{
	game->philo_num = ft_atoi(input[1]);
	game->die_time = ft_atoi(input[2]);
	game->eat_time = ft_atoi(input[3]);
	game->sleep_time = ft_atoi(input[4]);
	game->must_eat_num = 0;
	game->is_died = FALSE;
	game->eat_all = FALSE;
	game->start_time = 0;
	if (input_num == 6)
		game->must_eat_num = ft_atoi(input[5]);
	if (!init_mutex(game)
		|| !init_philo(game))
		return (MAL_ERR);
	return (0);
}
