LIBFT = libft.a
LIBFT_PATH = libft
MINISHELL = minishell
CC = cc
AR = ar rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

FILES = others/signals.c parser/parser_line.c parser/parser_word.c parser/parser_aux.c parser/parser_command.c \
	parser/commands.c parser/vars.c parser/quotes.c parser/alias.c launcher/launcher.c \
	parser/env.c launcher/pipex.c launcher/protected.c launcher/redirects.c launcher/sons.c \
	builtins/builtins1.c builtins/builtins2.c builtins/exit.c others/clean.c minishell.c others/init_files.c

OBJ =$(FILES:.c=.o)

all:  ${MINISHELL}

${LIBFT_PATH}/${LIBFT}:
		make all -C ${LIBFT_PATH}

${MINISHELL}: ${OBJ} ${LIBFT_PATH}/${LIBFT}
		${CC} ${OBJ} ${LIBFT_PATH}/${LIBFT} -lreadline -o ${MINISHELL}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
		make clean -C ${LIBFT_PATH}
		${RM} ${LIBFT} libft.h ${OBJ}

fclean: clean
		@make fclean -C ${LIBFT_PATH}
		${RM} ${MINISHELL}

re: fclean all

.phony = all clean fclean re
