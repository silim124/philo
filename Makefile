# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 18:45:01 by silim             #+#    #+#              #
#    Updated: 2021/10/31 14:16:45 by silim            ###   ########.fr        #
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

OBJ	=	$(SRCS: .c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJ)
			gcc $(FLAGS) -I. -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
