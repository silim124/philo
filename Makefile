# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 18:45:01 by silim             #+#    #+#              #
#    Updated: 2021/12/21 19:19:44 by silim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS	=	-Wall -Wextra -Werror

SRCS	=	srcs/main.c\
			srcs/init.c\
			srcs/error_handler.c\
			srcs/utils.c\
			srcs/execute.c\
			srcs/thread_manager.c\

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
