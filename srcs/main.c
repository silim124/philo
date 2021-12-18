/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:23:11 by silim             #+#    #+#             */
/*   Updated: 2021/11/30 18:47:37 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positive_num(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

static int	is_invalid_input(int input_num, char **input)
{
	int	i;
	if (input_num != 5 && input_num != 6)
		return (INPUT_COUNT);
	i = 0;
	while (++i < input_num)
		if (!is_positive_num(input[i]))
			return (NEGATIVE_INPUT);
	return (0);
}

int	main(int argc, char **argv)
{
	int	error_code;
	t_game	game;

	if ((error_code = is_invalid_input(argc, argv))
		|| (error_code = init_game(&game, argc, argv))
		|| (error_code = start_game(&game, game.philo)))
		return (put_error(error_code));
	return (0);
}
