# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydavis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/01 04:18:14 by ydavis            #+#    #+#              #
#    Updated: 2020/02/01 04:24:27 by ydavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror ../libft/libft.a
SRC = check_args.c encoder.c errors.c free.c get_strings.c helpful.c init.c\
	  label.c main.c op.c parser.c read_file.c size_help.c string_size.c\
	  token.c utils.c values.c
HDR = op.h main.h
NAME = asm
LIBMAKE = ../libft

all:		$(NAME)

$(NAME):	$(LIBMAKE) $(SRC) $(HDR)
	@make -C $(LIBMAKE)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	@make -C $(LIBMAKE) clean

fclean:	clean
	@make -C $(LIBMAKE) fclean
	@rm -rf $(NAME)

re:		fclean all

debug:
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -g
