# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achazal <achazal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:54:29 by achazal           #+#    #+#              #
#    Updated: 2014/12/13 12:55:35 by achazal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------Compilateur------------------#
CC = cc
CFLAGS = -Wall -Werror -Wextra -I./includes -g
#--------------Name-------------------------#
NAME = computor

#--------------Sources----------------------#
FILES =	main.c

OBJECT = $(patsubst %.c,%.o,$(FILES))
BASEDIR = srcs

CURRENT_DIR = $(shell pwd)/$(NAME)
#--------------Actions----------------------#

all:$(NAME)

$(NAME):
	@$(CC) -c $(CFLAGS)	$(addprefix $(BASEDIR)/, $(FILES))
	@$(CC) -o $(NAME) $(OBJECT) -L /usr/lib -ltermcap

clean :
		rm -Rf $(OBJECT)

fclean: clean
		rm -Rf $(NAME)

re: fclean all

.PHONY: all, fclean, clean, re 
