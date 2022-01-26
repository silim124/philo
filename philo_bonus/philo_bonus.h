/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:38:10 by silim             #+#    #+#             */
/*   Updated: 2022/01/27 04:19:48 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define FALSE 0
# define TRUE 1

# define DIED 0
# define SLEEP 1
# define EAT 2
# define THINK 3

# define INPUT_ERR 1
# define MAL_ERR 2
# define INTERNAL_ERR 3

# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_philo
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	int				eat_num;
	long long		last_eat_time;
	pthread_t		thread;
	struct s_game	*game;
	pid_t			pid;
}	t_philo;

typedef struct s_game
{
	int				is_died;
	int				philo_num;
	int				must_eat_num;
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	long long		start_time;
	sem_t			*s_check;
	sem_t			*s_fork;
	sem_t			*s_print;
	t_philo			philo[250];
}	t_game;

/*
** utils.c
*/
int			ft_atoi(const char *str);
long long	current_time(void);
long long	diff_time(long long now, long long past);
void		spend_time(t_game *game, int status);
void		put_philo(t_game *game, char *str, int philo_id);

/*
** error_handler.c
*/
int			put_error(int error_code);

/*
** init.c
*/
int			init_game(t_game *game, int input_num, char **input);
void		init_philo(t_game *game);
int			init_semaphore(t_game *game);

/*
** philo.c
*/
void		execute(void *void_philo);
void		eat(t_game *game, t_philo *philo);
void		end_game(t_game *game);
void		*check_death(void *void_philo);
void		put_dead(t_game *game, int philo_id);

/*
** main.c
*/
int			start_game(t_game *game, t_philo *philo);

#endif
