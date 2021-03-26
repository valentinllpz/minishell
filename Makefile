# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 17:58:20 by vlugand-          #+#    #+#              #
#    Updated: 2021/03/26 15:12:42 by vlugand-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

SRCS		= 	srcs/parser.c\
				srcs/lexer.c\
				srcs/utils.c\
				srcs/main_test.c

CC			= 	gcc
OBJS		= 	${SRCS:.c=.o}
OBJS_BONUS 	= 	${SRCS_BONUS:.c=.o}
CFLAGS		= 	-Wall -Wextra -Werror -fsanitize=address -g3
LIBS		=	-L libft -lft
RM			= 	rm -f

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

lbft:
			@echo "$(tput bold)\033[0;35m\033[1mPreparing Libft...\033[0m$(tput sgr0)"
			@make bonus -C libft
			@echo "\033[0;36m\033[1mLibft is ready to use.\033[0m"
			
${NAME}:	${OBJS_PATH} ${OBJS} lbft
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}
			@echo "\033[0;32m\033[1mMinishell is now ready!\033[0m"

clean:		
			@make clean -C libft
			${RM} ${OBJS} ${OBJS_BONUS}
			@echo "\033[0;35m\033[1mCleaned all .o files.\033[0m"

fclean:		clean
			@make fclean -C libft
			${RM} ${NAME}
			@echo "\033[0;35m\033[1mCleaned all .o files and executable.\033[0m"

re:			fclean all

.PHONY:		all clean fclean re bonus rebonus
