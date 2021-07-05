# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 17:58:20 by vlugand-          #+#    #+#              #
#    Updated: 2021/07/05 16:52:31 by vlugand-         ###   ########.fr        #
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
CFLAGS		= 	-Wall -Wextra -Werror
LIBS		=	-L libft -lft
RM			= 	rm -f
LIBFT		=	libft/libft.a

all:		${LIBFT} ${NAME}

.c.o:
			${CC} ${CFLAGS} -I includes -c $< -o ${<:.c=.o}

${LIBFT}:
			@make -C libft
			@echo "\033[0;36m\033[1mLibft is ready to use.\033[0m"
			#For any change in libft please use "make re" with this Makefile or "make" on the Makefile located in ./libft/

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBS} -lncurses
			@echo "\033[0;32m\033[1mMinishell is now ready!\033[0m"
			@echo ""
			@echo "\033[92m███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      "
			@echo "\033[93m████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      "
			@echo "\033[91m██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      "
			@echo "\033[95m██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      "
			@echo "\033[96m██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████  \033[0mby ade-garr & vlugand-"
			@echo ""

clean:		
			@make clean -C libft
			${RM} ${OBJS}
			@echo "\033[0;35m\033[1mCleaned all .o files.\033[0m"

fclean:		
			@make fclean -C libft
			${RM} ${OBJS}
			${RM} ${NAME}
			@echo "\033[0;35m\033[1mCleaned all .o files and executable.\033[0m"

re:			fclean all

.PHONY:		all clean fclean re bonus
