# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 17:58:20 by vlugand-          #+#    #+#              #
#    Updated: 2021/04/30 15:58:30 by ade-garr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

SRCS		= 	srcs/lexer.c\
				srcs/parser1.c\
				srcs/parser2.c\
				srcs/utils.c\
				srcs/utils1.c\
				srcs/utils2.c\
				srcs/utils3.c\
				srcs/print_lexer_parser.c\
				srcs/free_ast.c\
				srcs/expansion.c\
				srcs/expansion2.c\
				srcs/execute1.c\
				srcs/execute2.c\
				srcs/execute3.c\
				srcs/readline1.c\
				srcs/readline2.c\
				srcs/readline3.c\
				srcs/redirections.c\
				srcs/terminal.c\
				srcs/safer_libft.c\
				srcs/quotes.c\
				srcs/main.c

CC			= 	gcc
OBJS		= 	${SRCS:.c=.o}
OBJS_BONUS 	= 	${SRCS_BONUS:.c=.o}
CFLAGS		= 	-Wall -Wextra -Werror
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
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME} -lncurses
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
