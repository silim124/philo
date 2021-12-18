/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:38:10 by silim             #+#    #+#             */
/*   Updated: 2021/11/30 18:02:50 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# define FALSE 0
# define TRUE 1

# define DIED 0
# define SLEEP 1
# define EAT 2
# define THINK 2
# define PUT_FORK 3

# define INPUT_COUNT 1
# define NEGATIVE_INPUT 2
# define MAL_ERR 3
# define INTERNAL_ERR 4

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_game
{
	int	eat_all;
	int	is_died;
	int	philo_num;
	int	must_eat_num;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	long long	start_time;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	m_eating;
	pthread_mutex_t	m_print;
	struct s_philo	*philo;
}	t_game;

typedef struct s_philo
{
	int	id;
	int	left_fork_id;
	int	right_fork_id;
	int	eat_num;
	unsigned long	last_eat_time;
	pthread_t		thread;
	t_game	*game;
}	t_philo;

/*
** utils.c
*/
int	ft_atoi(const char *str);
long long	current_time(void);
long long	diff_time(long long now, long long past);
void	spend_time(t_game *game, int	status);
void	put_philo(t_game *game, char *str, int philo_id);

/*
** error_handler.c
*/
int	put_error(int error_code);

/*
** init.c
*/
int	init_game(t_game *game, int	input_num, char **input);
int	init_philo(t_game *game);
int	init_mutex(t_game *game);

/*
** thread_manager.c
*/
int	start_game(t_game *game, t_philo *philo);
void	end_game(t_game *game, t_philo *philo);
void	check_death(t_game *game, t_philo *philo);
void	check_eat_all(t_game *game, t_philo *philo);

/*
** execute.c
*/
void	*execute(void *void_philo);
void	eat(t_game *game, t_philo *philo);
int	prepare_eat(t_game *game, t_philo *philo);

#endif