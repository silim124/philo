/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:22:59 by silim             #+#    #+#             */
/*   Updated: 2021/11/30 18:02:05 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long long	result;
	int			i;

	i = 0;
	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
		i++;
	}
	if (result < -2147483648 || result > 2147483647)
		return (-sign);
	return (sign * result);
}

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	diff_time(long long now, long long past)
{
	return (now - past);
}

void	spend_time(t_game *game, int status)
{
	long long	start_time;
	long long	limit_time;

	if (status == EAT)
		limit_time = (long long)game->eat_time;
	else if (status == SLEEP)
		limit_time = (long long)game->sleep_time;
	start_time = current_time();
	while (game->is_died == 0)
	{
		if (diff_time(current_time(), start_time) >= limit_time)
			break;
		usleep(100);
	}
}

void	put_philo(t_game *game, char *str, int philo_id)
{
	pthread_mutex_lock(&(game->m_print));
	if (game->is_died == 0)
	{
		printf("%lldms", current_time() - game->start_time);
		printf(" %d ", philo_id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(game->m_print));
}
