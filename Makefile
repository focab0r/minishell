LIBFT = libft.a
LIBFT_PATH = libft
MINISHELL = minishell
CC = gcc
AR = ar rcs
RM = rm -rf
#CFLAGS = -Wall -Wextra -Werror

FILES = minishell.c parser.c commands.c alias.c vars.c execute.c signals.c

all:  ${MINISHELL}

${LIBFT}:
		make all -C ${LIBFT_PATH}

${MINISHELL}: ${FILES} ${LIBFT}
		gcc ${FILES} ${LIBFT_PATH}/${LIBFT} -lreadline -o ${MINISHELL} 

clean:
		make clean -C ${LIBFT_PATH}
		${RM} ${LIBFT} libft.h

fclean: clean
		@make fclean -C ${LIBFT_PATH}
		${RM} ${MINISHELL}

re: fclean all

.phony = all clean fclean re
