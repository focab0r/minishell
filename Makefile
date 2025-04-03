LIBFT = libft.a
LIBFT_PATH = libft
MINISHELL = minishell
CC = gcc
AR = ar rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

FILES = signals.c parser/parser1.c parser/parser2.c parser/commands.c parser/vars.c \
	parser/quotes.c parser/alias.c launcher/launcher.c launcher/pipex.c \
	launcher/protected.c launcher/redirects.c launcher/sons.c \
	builtins/builtins1.c builtins/builtins2.c builtins/exit.c clean.c minishell.c

OBJ =$(FILES:.c=.o)

all:  ${MINISHELL}

${LIBFT}:
		make all -C ${LIBFT_PATH}

${MINISHELL}: ${OBJ} ${LIBFT}
		gcc ${FILES} ${LIBFT_PATH}/${LIBFT} -lreadline -o ${MINISHELL}

%.o: %.c
	${CC} ${CCFLAGS} -c $< -o $@

clean:
		make clean -C ${LIBFT_PATH}
		${RM} ${LIBFT} libft.h ${OBJ}

fclean: clean
		@make fclean -C ${LIBFT_PATH}
		${RM} ${MINISHELL}

re: fclean all

.phony = all clean fclean re
