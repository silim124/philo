/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:23:19 by silim             #+#    #+#             */
/*   Updated: 2021/12/20 10:17:57 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_putstr_fd(char *s, int fd)
{
	if (!(s))
		return ;
	write(fd, s, ft_strlen(s));
}

int	put_error(int error_code)
{
	if (error_code == INPUT_COUNT)
		ft_putstr_fd("wrong input count\n", STDERR_FILENO);
	else if (error_code == INVALID_INPUT)
		ft_putstr_fd("should not put any negative \
			or zero input\n", STDERR_FILENO);
	else if (error_code == MAL_ERR)
		ft_putstr_fd("malloc error\n", STDERR_FILENO);
	else if (error_code == INTERNAL_ERR)
		ft_putstr_fd("internal error\n", STDERR_FILENO);
	return (1);
}
