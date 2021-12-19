/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:38:51 by silim             #+#    #+#             */
/*   Updated: 2021/12/19 18:50:47 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_game *game, t_philo *philo)
{
	int	i;

	while (!game->eat_all)
	{
		i = 0;
		while (i < game->philo_num)
		{
			if (current_time() - philo->last_eat_time > game->die_time)
			{
				pthread_mutex_lock(&game->m_check_death);
				put_philo(game, "is died", i);
				game->is_died = TRUE;
				pthread_mutex_unlock(&game->m_check_death);
				return ;
			}
			usleep(100);
			i++;
		}
		i = -1;
		while (game->must_eat_num && philo[i].eat_num >= game->must_eat_num)
		{
			if (++i == game->philo_num)
			{
				game->eat_all = TRUE;
				return ;
			}
		}
	}
}

void	end_game(t_game *game, t_philo *philo)
{
	int	i;

	i = 0;
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
		if (pthread_create(&(philo[i].thread), NULL, execute, (void *)&(philo[i])))
			return (INTERNAL_ERR);
		i++;
	}
	check_death(game, philo);
	end_game(game, philo);
	return (0);
}
