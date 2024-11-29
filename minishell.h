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

typedef struct {
	int 	background_commands;
	int 	**waitpid_estructure;
	char	**inputs;
	int		*ncommands;
} twaitpid;

//Tokenize
extern tline * tokenize(char *str);
//Commands
void print_line(tline *line);
//vars
//void replace_vars(t_minishell m, t_line *line);
//Execute
int *execute_commands(tline *line, twaitpid *pid_stock);
//Signals
void sig_handler(int sig, siginfo_t *info, void *context);
//Builtins
int		is_builtin(char *str);
void	builtin_cd(tcommand t);
void	builtin_jobs(tcommand t, twaitpid *pid_stock);
void	builtin_fg(tcommand t, twaitpid *pid_stock);
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
//PID stock
void add_pids(twaitpid *pid_stock, int *aux, int ncommands, char *input);
int check_if_line_is_dead(int ncommands, int *waitpid_list);
void show_line_as_jobs(int num, char *input);
void delete_dead_pids_as_jobs(twaitpid *pid_stock);
void exec_line_as_job(int nline, twaitpid *pid_stock);
void exec_line_as_job(int nline, twaitpid *pid_stock);


#endif