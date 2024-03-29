# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgranule <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/12 17:30:27 by hgranule          #+#    #+#              #
#    Updated: 2019/05/16 18:20:36 by hgranule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
LIBFT = libft.a

CUR_DIR = $(shell pwd)
LIB_DIR = $(CUR_DIR)/libft
OBJ_DIR = $(CUR_DIR)/objects

SRC =	file_parser.c fillit_handlers.c fillit_matrix.c \
		main.c tetromino_parser.c x_algorithm.c \
		safe_malloc.c
OBJ =	$(SRC:.c=.o)

SRCS = $(addprefix $(CUR_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

CC = gcc
CCFLAGS = -Wall -Werror -Wextra $(LIBFT_H)
LIBFT_H = -I $(LIB_DIR)/includes

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@make -C $(CUR_DIR) $(OBJS)

$(LIBFT):
	@make -C $(LIB_DIR) $(LIBFT)

$(OBJ_DIR)/%.o: $(CUR_DIR)/%.c
	@echo "Compiling $< to $@"
	@$(CC) $(CCFLAGS) -c $< -o $@ 

$(NAME):
	@echo "Compiling Libft..."
	@make -C $(CUR_DIR) $(LIBFT)
	@echo "Creating objects directory...\n"
	@make -C $(CUR_DIR) $(OBJ_DIR)
	@echo "\nCompiling executable..."
	@$(CC) $(CCFLAGS) $(LIBFT_H) $(LIB_DIR)/$(LIBFT) $(OBJS) -o $(NAME)
	@echo "\nCOMPILED\n"

debug:
	@echo "Compiling Libft..."
	@make -C $(CUR_DIR) $(LIBFT)
	@echo "Compiling with debug flag..."
	@$(CC) $(CCFLAGS) $(LIBFT_H) $(LIB_DIR)/$(LIBFT) $(SRCS) -o $(NAME) -g
	@echo "\nCOMPILED\n"
	

clean:
	@echo "Cleaning object files..."
	@make -C $(LIB_DIR) fclean
	@rm -rf $(OBJ_DIR)
	@echo "\nCLEANED\n"

fclean: clean
	@echo "Deleting executable -> $(NAME)..."
	@rm -f $(NAME)
	@echo "\nDONE\n"

re: fclean all
