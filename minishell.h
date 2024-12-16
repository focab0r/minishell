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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct scommand
{
	char	*filename;
	int		argc;
	char	**argv;
}	tcommand;

typedef struct sline
{
	int			ncommands;
	tcommand	*commands;
	char		*redirect_input;
	char		*redirect_output;
	char		*redirect_error;
	int			background;
}	tline;

typedef struct swaitpid
{
	int		background_commands;
	int		**waitpid_estructure;
	char	**inputs;
	int		*ncommands;
}	twaitpid;

extern int g_job;
extern twaitpid *pid_stock;
extern int waiting;

//Tokenize
extern	tline *tokenize(char *str);
//Execute
int		*execute_commands(tline *line);
//Builtins
int		is_builtin(char *str);
void	builtin_cd(tcommand t);
void	builtin_jobs();
void	builtin_fg(tcommand t);
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
void	add_pids(int *aux, int ncommands, char *input);
int		check_if_line_is_dead(int ncommands, int *waitpid_list, int pid);
void show_line_as_jobs(int num, char *input, int is_dead);
void	refresh_pids_cache(int pid);
void	exec_line_as_job(int nline);
void	exec_line_as_job(int nline);

#endif