# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgranule <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/12 17:30:27 by hgranule          #+#    #+#              #
#    Updated: 2019/05/13 05:46:19 by hgranule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
LIBFT = libft.a

CUR_DIR = $(shell pwd)
LIB_DIR = $(CUR_DIR)/libft
OBJ_DIR = $(CUR_DIR)/objects

SRC =	file_parser.c fillit_handlers.c fillit_matrix.c \
		main.c tetromino_parser.c x_algorithm.c
OBJ =	$(SRC:.c=.o)

SRCS = $(addprefix $(CUR_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

CC = gcc
CCFLAGS = -Wall -Werror -Wextra $(LIBFT_H)
LIBFT_H = -I $(LIB_DIR)/includes

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	make -C $(CUR_DIR) $(OBJS)

$(LIBFT):
	make -C $(LIB_DIR) $(LIBFT)

kek:
	echo $(SRCS)

$(OBJ_DIR)/%.o: $(CUR_DIR)/%.c
	$(CC) $(CCFLAGS) -c $< -o $@ 

$(NAME):
	make -C $(CUR_DIR) $(LIBFT)
	make -C $(CUR_DIR) $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(LIBFT_H) $(LIB_DIR)/$(LIBFT) $(OBJS) -o $(NAME)

clean:
	@make -C $(LIB_DIR) fclean
	@rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all