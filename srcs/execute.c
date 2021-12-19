/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:39:48 by silim             #+#    #+#             */
/*   Updated: 2021/12/19 16:56:15 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(&(game->m_eating));
	put_philo(game, "is eating", philo->id);
	philo->last_eat_time = current_time();
	pthread_mutex_unlock(&(game->m_eating));
	philo->eat_num += 1;
	spend_time(game, EAT);
}

int	prepare_eat(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(&(game->m_fork[philo->left_fork_id]));
	put_philo(game, "has taken a fork", philo->id);
	pthread_mutex_lock(&(game->m_fork[philo->right_fork_id]));
	put_philo(game, "has taken a fork", philo->id);
	eat(game, philo);
	pthread_mutex_unlock(&(game->m_fork[philo->left_fork_id]));
	pthread_mutex_unlock(&(game->m_fork[philo->right_fork_id]));
	if (game->eat_all)
		return (0);
	return (1);
}

void	*execute(void *void_philo)
{
	t_philo	*philo;
	t_game *game;

	philo = (t_philo *)void_philo;
	game = philo->game;
	if (philo->id % 2)
		usleep(200);
	while (game->is_died == 0)
	{
		if (!prepare_eat(game, philo))
			break;
		put_philo(game, "is sleeping", philo->id);
		spend_time(game, SLEEP);
		put_philo(game, "is thinking", philo->id);
	}
	return (0);
}
