# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpeng <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/05 21:58:24 by kpeng             #+#    #+#              #
#    Updated: 2018/09/05 22:02:36 by kpeng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

SRC = srcs/*.c

INCLUDES = includes

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra -O3 -o $(NAME) $(SRC)
clean:
	/bin/rm -f
fclean:
	/bin/rm -f $(NAME)
re: fclean all
