/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:38:51 by silim             #+#    #+#             */
/*   Updated: 2021/12/21 20:50:18 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	check_eat_all(t_game *game, t_philo *philo)
{
	int	i;

	i = -1;
	while (game->must_eat_num && philo[++i].eat_num >= game->must_eat_num)
	{
		if (i == game->philo_num - 1)
		{
			game->eat_all = TRUE;
			return ;
		}
	}
}

void	check_death(t_game *game, t_philo *philo)
{
	int	i;

	while (!game->eat_all)
	{
		i = 0;
		while (i < game->philo_num)
		{
			if (current_time() - philo[i].last_eat_time > game->die_time)
			{
				pthread_mutex_lock(&game->m_check_death);
				put_philo(game, "died", i);
				game->is_died = TRUE;
				pthread_mutex_unlock(&game->m_check_death);
				return ;
			}
			usleep(50);
			i++;
		}
		check_eat_all(game, philo);
	}
}

void	end_game(t_game *game, t_philo *philo)
{
	int	i;

	i = 0;
	if (game->philo_num == 1)
		pthread_mutex_unlock(&(game->m_fork[0]));
	while (i < game->philo_num)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&(game->m_fork[i++]));
	}
	free(game->philo);
	free(game->m_fork);
	pthread_mutex_destroy(&(game->m_eating));
	pthread_mutex_destroy(&(game->m_print));
}

int	start_game(t_game *game, t_philo *philo)
{
	int	i;

	i = 0;
	game->start_time = current_time();
	while (i < game->philo_num)
	{
		philo[i].last_eat_time = current_time();
		if (pthread_create(&(philo[i].thread), NULL, \
			execute, (void *)&(philo[i])))
			return (0);
		i++;
	}
	check_death(game, philo);
	end_game(game, philo);
	return (1);
}
