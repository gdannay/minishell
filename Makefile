# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdannay <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/05 13:24:06 by gdannay           #+#    #+#              #
#    Updated: 2018/01/05 13:48:12 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	srcs/minishell.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I includes -I libft

LFLAGS	=	-L libft -lft

CC		=	gcc

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			make -C libft
			$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o		:	%.c
			$(CC) -o $@ -c $< $(CFLAGS)

clean	:
			make clean -C libft
			rm -rf $(OBJS)

fclean	:
			make fclean -C libft
			rm -rf $(OBJS)
			rm -rf $(NAME)

re		:	fclean all