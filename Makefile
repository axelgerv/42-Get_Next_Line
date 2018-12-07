# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axelgerv <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/07 12:33:14 by axelgerv          #+#    #+#              #
#    Updated: 2018/12/07 12:34:28 by axelgerv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all :
	make -C libft/ fclean && make -C libft/
	clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
	 clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	  clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft
