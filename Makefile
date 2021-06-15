# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 17:58:20 by vlugand-          #+#    #+#              #
#    Updated: 2021/06/15 19:18:22 by ade-garr         ###   ########.fr        #
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
				srcs/utils4.c\
				srcs/utils5.c\
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
				srcs/signal.c\
				srcs/quotes.c\
				srcs/builtins.c\
				srcs/builtin_cd.c\
				srcs/builtin_cd2.c\
				srcs/builtin_export.c\
				srcs/builtin_exit.c\
				srcs/builtin_env.c\
				srcs/builtin_pwd.c\
				srcs/builtin_unset.c\
				srcs/builtin_echo.c\
				srcs/heredoc.c\
				srcs/backslash.c\
				srcs/main.c

CC			= 	gcc
OBJS		= 	${SRCS:.c=.o}
OBJS_BONUS 	= 	${SRCS_BONUS:.c=.o}
CFLAGS		= 	-Wall -Wextra -Werror -g3
LIBS		=	-L libft -lft
RM			= 	rm -f

all:		${NAME}
			@echo ""
			@echo "███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      "
			@echo "████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      "
			@echo "██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      "
			@echo "██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      "
			@echo "██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████  by ade-garr & vlugand-"
			@echo ""
	
			

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
