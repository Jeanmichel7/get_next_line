# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrasser <jrasser@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 19:03:02 by Jeanmichel7       #+#    #+#              #
#    Updated: 2023/09/01 20:23:34 by jrasser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= get_next_line.c \
				get_next_line_utils.c \
				main.c

SRCS_BONUS	= get_next_line_bonus.c \
				get_next_line_utils_bonus.c \
				main_bonus.c

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

NAME		= get_next_line.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

CPPFLAGS	= -I./

$(NAME):	$(OBJS)
					${CC} ${CFLAGS} -D BUFFER_SIZE=42 $(OBJS) -o tester

all:			$(NAME)

bonus:	$(OBJS_BONUS)
			${CC} ${CFLAGS} -D BUFFER_SIZE=42 $(OBJS_BONUS) -o tester_bonus

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME) test a.out *.o tester tester_bonus

re:			fclean all

.PHONY:		all clean fclean re
