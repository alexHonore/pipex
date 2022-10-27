# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 20:03:26 by anshimiy          #+#    #+#              #
#    Updated: 2022/10/27 17:43:44 by anshimiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =  src/main.c			\
		src/pipex.c			\

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
	make -C ./my_lib
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) ./my_lib/mylib.a

clean: 
	$(MAKE) -C ./my_lib clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
