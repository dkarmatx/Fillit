# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgranule <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/12 17:30:27 by hgranule          #+#    #+#              #
#    Updated: 2019/05/12 17:33:43 by hgranule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

all: $(NAME)

$(NAME):
	gcc libft/srcs/*/*.c -I libft/includes *.c -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all