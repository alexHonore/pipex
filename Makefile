# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 20:03:26 by anshimiy          #+#    #+#              #
#    Updated: 2022/10/28 17:52:46 by anshimiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCDIR = src/
SRCS =  src/main.c			\
		src/pipex.c			\

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

# .o files in bin
OBJDIR	=	bin/
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))


all: $(NAME)

$(NAME):	$(OBJS)
	make -C ./my_lib
	$(HIDE) $(CC) $(CFLAGS) $(OBJS) -o $(NAME) ./my_lib/mylib.a

# Compiles sources into objects
$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c| $(OBJDIR)
	$(HIDE) $(CC) $(CFLAGS) -c $< -o $@

# Creates directory for binaries
$(OBJDIR):
	$(HIDE) mkdir -p $@

clean: 
	$(MAKE) -C ./my_lib clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C ./my_lib fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
