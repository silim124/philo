/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:23:11 by silim             #+#    #+#             */
/*   Updated: 2021/12/21 20:49:39 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_positive_num(char *s)
{
	if (!s)
		return (0);
	if (*s && *s == '0')
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

static int	is_valid_input(int input_num, char **input)
{
	int	i;

	if (input_num != 5 && input_num != 6)
		return (0);
	i = 0;
	while (++i < input_num && input[i])
		if (!is_positive_num(input[i]) || !(ft_atoi(input[i])))
			return (0);

	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!is_valid_input(argc, argv))
		return (put_error(INPUT_ERR));
	if (!init_game(&game, argc, argv))
		return (put_error(MAL_ERR));
	if (!start_game(&game, game.philo))
		return (put_error(INTERNAL_ERR));
	return (0);
}
