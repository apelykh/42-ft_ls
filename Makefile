#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apelykh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:49:03 by apelykh           #+#    #+#              #
#    Updated: 2017/05/02 18:49:04 by apelykh          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

FLAGS = -Wall -Werror -Wextra
CC = gcc $(FLAGS)
NAME = ft_ls
LIB_DIR = libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
SRC_DIR = src/
SRC_FILES = args_parsing.c arr_sorting.c error_handling.c ft_ls.c list_misc.c \
	node_ops.c list_ops.c main.c misc.c printing.c arr_sorting_features.c \
	list_sorting_features.c list_sorting.c 
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)
INCLUDE_DIR = includes

.PHONY: all

all: $(NAME)
	

makelib:
	@ make -C $(LIB_DIR)

libclean:
	@ make -C $(LIB_DIR) clean

libfclean:
	@ make -C $(LIB_DIR) fclean

$(NAME): $(OBJ) makelib
	@ $(CC) $(OBJ) -L$(LIB_DIR) -lft -o $@

.c.o: $(SRC)
	@ $(CC) -I $(LIB_DIR)/includes -I includes -c $^ -o $@

clean: libclean
	@ /bin/rm -f $(OBJ)

fclean: clean
	@ /bin/rm -f $(NAME)

re: fclean all
