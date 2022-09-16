# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 23:55:45 by lbraz-te          #+#    #+#              #
#    Updated: 2022/09/16 16:04:44 by aazevedo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S := $(shell uname -s)

SRCS	= $(wildcard srcs/*.c) \
			$(wildcard srcs/parsing/*.c) \
			$(wildcard srcs/rendering/*.c) \
			$(wildcard srcs/utils/*.c)

ifeq ($(USER),tony)
	MINILIBX_DIR = includes/minilibx_opengl_20191021
	MINILIBX_FLAGS = -L${MINILIBX_DIR} -lmlx -framework OpenGL -framework AppKit
	MINILIBX_LIB_FILE = libmlx.a
else ifeq ($(UNAME_S),Darwin)
	MINILIBX_DIR = includes/minilibx_macos
	MINILIBX_FLAGS = -L${MINILIBX_DIR} -lmlx -framework OpenGL -framework AppKit
	MINILIBX_LIB_FILE = libmlx.dylib
else
	MINILIBX_DIR = includes/minilibx_linux
	MINILIBX_FLAGS = -I /usr/X11/include -g -L${MINILIBX_DIR} -lmlx_Linux -L /usr/lib -Imlx_linux -lmlx -lXext -lX11 -lm
	MINILIBX_LIB_FILE = libmlx_Linux.a
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

${NAME}: ${MINILIBX_LIB_FILE} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${MINILIBX_FLAGS}  -o ${NAME} ${LFLAGS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${MINILIBX_LIB_FILE}: ./${MINILIBX_DIR}
	make -C ./${MINILIBX_DIR}
	cp	./${MINILIBX_DIR}/${MINILIBX_LIB_FILE} ${MINILIBX_LIB_FILE}
	cp ./${MINILIBX_DIR}/mlx.h includes/mlx.h

clean:
	${RM} ${MINILIBX_LIB_FILE}:
	${RM} includes/mlx.h
	${RM} ${OBJS}

fclean: clean
	make clean -C ./${MINILIBX_DIR}
	${RM} ${NAME}

re:	fclean all

norm:
	norminette includes/miniRT.h ${SRCS}

.PHONY:			all clean fclean re
