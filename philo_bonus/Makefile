# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 18:45:01 by silim             #+#    #+#              #
#    Updated: 2022/01/27 04:17:37 by silim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

FLAGS	=	-Wall -Wextra -Werror

SRCS	=	srcs/main.c\
			srcs/init.c\
			srcs/error_handler.c\
			srcs/philo.c\
			srcs/utils.c

OBJS	= $(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
			gcc $(FLAGS) -I. -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re	:	fclean all

.PHONY:	clean fclean re
