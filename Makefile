MINISHELL = minishell
CC = gcc
AR = ar rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

FILES = minishell.c execute.c builtins.c get_next_line.c get_next_line_utils.c pid_stocks.c

all:  ${MINISHELL}

${MINISHELL}: ${FILES} ${LIBFT}
		${CC} ${CFLAGS} ${FILES} libparser_64.a -o ${MINISHELL} -static

fclean:
		${RM} ${MINISHELL}

re: fclean all

.phony = all clean fclean re
