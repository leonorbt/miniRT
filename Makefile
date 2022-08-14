# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 23:55:45 by lbraz-te          #+#    #+#              #
#    Updated: 2022/08/14 23:34:20 by lbraz-te         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(wildcard srcs/*.c) # \
			# $(wildcard srcs/parsing/*.c)

OBJS	= ${SRCS:.c=.o}

INCLUDES = -I.
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra -fsanitize=address -g

MAKE	=	make

NAME	=	miniRT

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

all:	${NAME} ${OBJS}

${NAME}:${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY:			all clean fclean re
