MINISHELL = minishell
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -static

FILES = minishell.c execute.c builtins.c get_next_line.c get_next_line_utils.c pid_stocks.c

all:  ${MINISHELL}

${MINISHELL}: ${FILES}
		${CC} ${CFLAGS} ${FILES} libparser_64.a -o ${MINISHELL} 

fclean:
		${RM} ${MINISHELL}

re: fclean all

.phony = all clean fclean re
