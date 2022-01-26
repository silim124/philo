/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:38:51 by silim             #+#    #+#             */
/*   Updated: 2022/01/27 04:17:18 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	put_dead(t_game *game, int philo_id)
{
	sem_wait(game->s_print);
	printf("%lld", current_time() - game->start_time);
	printf(" %d ", philo_id + 1);
	printf("died\n");
	sem_post(game->s_print);
}

void	*check_death(void *void_philo)
{
	t_philo			*p;
	t_game			*g;

	p = (t_philo *)void_philo;
	g = p->game;
	while (42)
	{
		sem_wait(g->s_check);
		if (current_time() - p->last_eat_time > g->die_time)
		{
			put_dead(g, p->id);
			g->is_died = TRUE;
			sem_wait(g->s_print);
			exit(1);
		}
		sem_post(g->s_check);
		if (g->is_died)
			break ;
		usleep(1000);
		if (p->eat_num >= g->must_eat_num && g->must_eat_num != -1)
			break ;
	}
	return (0);
}

void	end_game(t_game *game)
{
	int	i;
	int	ret;

	i = 0;
	while (i < game->philo_num)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < game->philo_num)
				kill(game->philo[i].pid, 15);
			break ;
		}
		i++;
	}
	sem_close(game->s_fork);
	sem_close(game->s_print);
	sem_close(game->s_check);
	sem_unlink("/s_fork");
	sem_unlink("/s_print");
	sem_unlink("/s_check");
}

void	eat(t_game *game, t_philo *philo)
{
	sem_wait(game->s_fork);
	put_philo(game, "has taken a fork", philo->id);
	sem_wait(game->s_fork);
	put_philo(game, "has taken a fork", philo->id);
	sem_wait(game->s_check);
	put_philo(game, "is eating", philo->id);
	philo->last_eat_time = current_time();
	sem_post(game->s_check);
	spend_time(game, EAT);
	philo->eat_num += 1;
	sem_post(game->s_fork);
	sem_post(game->s_fork);
}

void	execute(void *void_philo)
{
	t_philo	*philo;
	t_game	*game;

	philo = (t_philo *)void_philo;
	game = philo->game;
	philo->last_eat_time = current_time();
	pthread_create(&(philo->thread), NULL, check_death, void_philo);
	if (philo->id % 2)
		usleep(15000);
	while (game->is_died == FALSE)
	{
		eat(game, philo);
		if (philo->eat_num >= game->must_eat_num
			&& game->must_eat_num != -1)
			break ;
		put_philo(game, "is sleeping", philo->id);
		spend_time(game, SLEEP);
		put_philo(game, "is thinking", philo->id);
	}
	pthread_join(philo->thread, NULL);
	if (game->is_died)
		exit(1);
	exit(0);
}
