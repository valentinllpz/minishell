# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 17:58:20 by vlugand-          #+#    #+#              #
#    Updated: 2021/06/25 19:22:17 by vlugand-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

SRCS		= 	srcs/lexer.c\
				srcs/parser1.c\
				srcs/parser2.c\
				srcs/utils_cond.c\
				srcs/utils_env1.c\
				srcs/utils_env2.c\
				srcs/utils_misc.c\
				srcs/utils_parsing.c\
				srcs/utils_safe.c\
				srcs/utils_termcaps.c\
				srcs/free1.c\
				srcs/free2.c\
				srcs/expansion1.c\
				srcs/expansion2.c\
				srcs/expansion3.c\
				srcs/execute1.c\
				srcs/execute2.c\
				srcs/execute3.c\
				srcs/readline1.c\
				srcs/readline2.c\
				srcs/readline3.c\
				srcs/redirections.c\
				srcs/termcaps.c\
				srcs/signal.c\
				srcs/builtins.c\
				srcs/builtin_cd.c\
				srcs/builtin_cd2.c\
				srcs/builtin_export.c\
				srcs/builtin_exit1.c\
				srcs/builtin_exit2.c\
				srcs/builtin_env.c\
				srcs/builtin_pwd.c\
				srcs/builtin_unset.c\
				srcs/builtin_echo.c\
				srcs/heredoc.c\
				srcs/str_cleanup.c\
				srcs/init.c\
				srcs/main.c

CC			= 	gcc
OBJS		= 	${SRCS:.c=.o}
OBJS_BONUS 	= 	${SRCS_BONUS:.c=.o}
CFLAGS		= 	-Wall -Wextra -Werror -g3 -fsanitize=address
LIBS		=	-L libft -lft
RM			= 	rm -f

all:		${NAME}
			@echo ""
			@echo "\033[92m███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      "
			@echo "\033[93m████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      "
			@echo "\033[91m██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      "
			@echo "\033[95m██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      "
			@echo "\033[96m██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████  \033[0mby ade-garr & vlugand-"
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
