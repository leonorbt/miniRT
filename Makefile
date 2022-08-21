# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 23:55:45 by lbraz-te          #+#    #+#              #
#    Updated: 2022/08/21 17:25:24 by lbraz-te         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(wildcard srcs/*.c) \
			$(wildcard srcs/parsing/*.c) \
			$(wildcard srcs/utils/*.c)

MINILIBX_DIR = includes/minilibx_mms_20200219
MINILIBX_FLAGS = -L${MINILIBX_DIR} -lmlx -framework OpenGL -framework AppKit

OBJS	= ${SRCS:.c=.o}

INCLUDES = -I.
CC		= cc
RM		= rm -f
#CFLAGS	= -Wall -Werror -Wextra -fsanitize=address -g
CFLAGS	= -Wall -Wextra -fsanitize=address -g

MAKE	=	make

NAME	=	miniRT

all:	${NAME} ${OBJS}

${NAME}: libmlx.dylib ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${MINILIBX_FLAGS} -o ${NAME} ${LFLAGS}

# ${NAME}: ${OBJS}
# ${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

libmlx.dylib: ./${MINILIBX_DIR}
	make -C ./${MINILIBX_DIR}
	cp	./${MINILIBX_DIR}/libmlx.dylib libmlx.dylib
	cp ./${MINILIBX_DIR}/mlx.h includes/mlx.h

clean:
	${RM} libmlx.dylib
	${RM} includes/mlx.h
	${RM} ${OBJS}

fclean: clean
	#make clean -C ./${MINILIBX_DIR}
	${RM} ${NAME}

re:	fclean all

norm:
	norminette ${SRCS}
	norminette includes/miniRT.h

.PHONY:			all clean fclean re
