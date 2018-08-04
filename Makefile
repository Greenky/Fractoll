#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/30 21:52:55 by vmazurok          #+#    #+#              #
#    Updated: 2018/03/30 21:52:58 by vmazurok         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = cc
CFLAGS =  -O3 -Wall -Wextra -Werror
GFX = -lmlx -framework OpenGL -framework AppKit
NAME = fractol
SRC = calkulation.c \
	dop_functions.c \
	julia.c \
	main.c \
	one_more_dop.c
BINS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(BINS)
	$(CC) $(CFLAGS) -o $(NAME) $(BINS) $(GFX)

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(BINS)

fclean: clean
	rm -f $(NAME)

re: fclean all