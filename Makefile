# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/16 16:42:45 by dbolilyi          #+#    #+#              #
#    Updated: 2018/06/18 17:03:06 by dbolilyi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = src/main.c \
	  src/update.c \
	  src/read.c \
	  src/out.c \
	  src/libfunctions.c \
	  src/image_put.c

OBJ = $(SRC:.c=.o)

FL = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

libft1:
	make -C ./libft

$(NAME): libft1 $(OBJ)
	gcc $(FL) $(OBJ) -o $(NAME) -L libft/ ./libft/libft.a -I ./fdf.h

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean \
	all

.PHONY: all clean fclean re libft

.NOTPARALLEL: all clean fclean re libft
