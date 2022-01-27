/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:23:14 by silim             #+#    #+#             */
/*   Updated: 2022/01/27 12:34:30 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	init_semaphore(t_game *game)
{
	sem_unlink("/s_fork");
	sem_unlink("/s_write");
	sem_unlink("/s_check");
	game->s_fork = sem_open("/s_fork", O_CREAT, S_IRWXU, game->philo_num);
	game->s_print = sem_open("/s_print", O_CREAT, S_IRWXU, 1);
	game->s_check = sem_open("/s_check", O_CREAT, S_IRWXU, 1);
	if (game->s_fork <= 0 || game->s_print <= 0 || game->s_check <= 0)
		return (0);
	return (1);
}

void	init_philo(t_game *game)
{
	int	i;

	i = game->philo_num;
	while (--i >= 0)
	{
		game->philo[i].id = i;
		game->philo[i].eat_num = 0;
		game->philo[i].last_eat_time = 0;
		game->philo[i].game = game;
	}
}

int	init_game(t_game *game, int input_num, char **input)
{
	game->philo_num = ft_atoi(input[1]);
	game->die_time = ft_atoi(input[2]);
	game->eat_time = ft_atoi(input[3]);
	game->sleep_time = ft_atoi(input[4]);
	game->must_eat_num = 0;
	game->is_died = FALSE;
	if (input_num == 6)
		game->must_eat_num = ft_atoi(input[5]);
	if (game->must_eat_num == 1)
		game->must_eat_num++;
	if (!init_semaphore(game))
		return (0);
	init_philo(game);
	return (1);
}
