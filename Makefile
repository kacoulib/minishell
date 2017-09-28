# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/11 14:57:17 by kacoulib          #+#    #+#              #
#    Updated: 2017/09/17 16:33:30 by kacoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Werror -Wextra -g
# CFLAGS		=	-Wall -Werror -Wextra -g3 -fsanitize=address
LIB			=	-L./libft -lft -lncurses
CPPFLAGS	=	-I header
SRCS		=	src/builtins/main.c \
				src/builtins/cd.c \
				src/builtins/echo.c \
				src/builtins/env.c \
				src/builtins/exit.c \
				src/builtins/setenv.c \
				src/builtins/unsetenv.c \
				src/flags/main.c \
				src/flags/crud.c \
				src/tools.c \
				src/shell.c \
				src/errors.c \
				src/prompt.c \
				src/signal.c \
				src/env_crud.c \
				src/setting_0.c \
				src/setting_1.c \
				src/convert.c \
				src/main.c

OBJS		=	$(SRCS:.c=.o)

all:		 	$(NAME)

$(NAME):		$(OBJS)
				Make -C ./libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB) $(CPPFLAGS)
clean:
				$(RM) $(OBJS)
				Make -C ./libft fclean

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

push:
				@git add .
				@echo "Enter Your Commit :"
				@read var1 ; git commit -m "$$var1"
				@echo "Enter The origin :"
				@read var2 ; git push origin "$$var2"

.PHONY:			all clean fclean re push
