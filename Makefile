# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/11 14:57:17 by kacoulib          #+#    #+#              #
#    Updated: 2017/09/11 14:57:18 by kacoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Werror -Wextra
LIB			=	-L./libft -lft -lncurses
CPPFLAGS	=	-Iincludes
SRCS		=	src/builtins.c \
				src/tools.c \
				src/setting_0.c \
				src/setting_1.c \
				src/minishell.c

OBJS		=	$(SRCS:.c=.o)

all:		 	$(NAME)

$(NAME):		$(OBJS)
				Make -C ./libft
				$(CC) -o $(NAME) $(OBJS) $(LIB) $(CPPFLAGS)
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
