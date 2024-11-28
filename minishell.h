/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <linux/limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

#define RESET   "\033[0m"
#define RED     "\e[1;31m"
#define GREEN   "\e[1;32m"
#define YELLOW  "\033[33m"
#define BLUE    "\e[1;34m"
#define MAGENTA "\e[1;35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct {
	char * filename;
	int argc;
	char ** argv;
} tcommand;

typedef struct {
	int ncommands;
	tcommand * commands;
	char * redirect_input;
	char * redirect_output;
	char * redirect_error;
	int background;
} tline;

//Tokenize
extern tline * tokenize(char *str);
//Commands
void print_line(tline *line);
//vars
//void replace_vars(t_minishell m, t_line *line);
//Execute
void execute_commands(tline *line);
//Signals
void sig_handler(int sig, siginfo_t *info, void *context);
//Builtins
int		is_builtin(char *str);
void	builtin_cd(char *argv, char **command);
//GNL
char	*get_next_line(int fd);
char	*read_continue(int *cr_f, int *offset, char **str, int *error);
char	*read_founded(int *error, char **str, char **str_saved, int i_offset);
char	*clean(char **str, int *error, int malloc_value, int op);
size_t	strlcpy_and_strlen(char *dest, const char *src, size_t n, int op);
char	*ft_realloc(char *str, int amount);
char	*prepare_str(int fd, char **str_saved, int *error, int op);
char	*read_while(int *cr_f, int *error, char **str, char **str_saved);
char	*str_saved_contains_n(char **str, int *i, char **str_saved);
char	*return_str(int error, char **str2, char **str, char **str_saved);



#endif