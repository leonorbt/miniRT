# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 23:55:45 by lbraz-te          #+#    #+#              #
#    Updated: 2022/08/22 22:52:35 by lbraz-te         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S := $(shell uname -s)

SRCS	= $(wildcard srcs/*.c) \
			$(wildcard srcs/parsing/*.c) \
			$(wildcard srcs/drawing/*.c) \
			$(wildcard srcs/utils/*.c)

ifeq ($(UNAME_S),Darwin)
	MINILIBX_DIR = includes/minilibx_macos
	MINILIBX_FLAGS = -L${MINILIBX_DIR} -lmlx -framework OpenGL -framework AppKit
else
	MINILIBX_DIR = includes/minilibx_linux
	MINILIBX_FLAGS = -I /usr/X11/include -g -L${MINILIBX_DIR} -lmlx_Linux -L /usr/lib -Imlx_linux -lmlx -lXext -lX11 -lm
endif

OBJS	= ${SRCS:.c=.o}

INCLUDES = -I.
CC		= cc
RM		= rm -f
#CFLAGS	= -Wall -Werror -Wextra -fsanitize=address -g
CFLAGS	= -Wall -Wextra -fsanitize=address -g

MAKE	=	make

NAME	=	miniRT

all:	${NAME} ${OBJS}

${NAME}: libmlx_Linux.a ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${MINILIBX_FLAGS}  -o ${NAME} ${LFLAGS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

libmlx.dylib: ./${MINILIBX_DIR}
	make -C ./${MINILIBX_DIR}
	cp	./${MINILIBX_DIR}/libmlx.dylib libmlx.dylib
	cp ./${MINILIBX_DIR}/mlx.h includes/mlx.h

libmlx_Linux.a: ./${MINILIBX_DIR}
	make -C ./${MINILIBX_DIR}
	cp	./${MINILIBX_DIR}/libmlx_Linux.a libmlx_Linux.a
	cp ./${MINILIBX_DIR}/mlx.h includes/mlx.h

clean:
	${RM} libmlx.dylib
	${RM} libmlx_Linux.a
	${RM} includes/mlx.h
	${RM} ${OBJS}

fclean: clean
	#make clean -C ./${MINILIBX_DIR}
	${RM} ${NAME}

re:	fclean all

norm:
	norminette includes/miniRT.h ${SRCS}

.PHONY:			all clean fclean re
