/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/03/29 18:38:42 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <linux/limits.h>

# define WRITE 1
# define READ 0

# define RESET   "\033[0m"
# define RED     "\e[1;31m"
# define GREEN   "\e[1;32m"
# define YELLOW  "\033[33m"
# define BLUE    "\e[1;34m"
# define MAGENTA "\e[1;35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

typedef struct s_command
{
	char	*filename;
	int		argc;
	char	**argv;
	pid_t	pid;
	char	*redirect_input;
	char	*redirect_output;
	char	*append_input;		//cambiarlo a heredoc_lim pls (de limitador)
	char	*append_output;
}	t_command;

typedef struct s_line
{
	int			ncommands;
	t_command	*commands;
	size_t		cmd_index;
	int			pipefd[2];
	int			pipefd2[2];
}	t_line;

typedef struct s_main
{
	int		pipefd[2];
	int		pipefd2[2];
	int		infd;
	int		outfd;
	pid_t	pid;
	pid_t	pid_last;
	pid_t	wpid;
	int		status;
	int		last_status;
	char	**cmd;
	int		heredoc;
	char	*lim;
	size_t	cmd_index;
}	t_main;

extern int	g_signal;

//Parser
int		parse_input(t_line **line, char *input, char **env);
void	print_line(t_line *line);
void	pass_till_comma(char *input, int *i);
int		is_special_char(char c);
void	scape_spaces(char *input, int *i);
char	*parse_word(char *input, int *i, char **env);
//Commands
void	add_argument_at_end(t_command *command, char *word);
void	init_command(t_command *l);
void	add_command_at_end(t_line *line, t_command *command);
//Vars
char	*replace_vars(char *command, char **env);
char	*check_env(char *word, char **env, int *env_num);
char	*get_env_header(char *env_var);
//Quotes
char	*escape_quotes(char *str);
//Alias
char	*expand_alias(char *word, char **env);
//Builtin
int		is_builtin(char *str);
void	builtin_echo(t_command command);
void	builtin_cd(t_command command);
void	builtin_pwd(void);
void	builtin_env(char **env);
void	builtin_export(char ***env, t_command command);
void	builtin_unset(char ***env, t_command command);
//Launcher
void	execute_commands(t_line *line, char ***env);
void	save_exit_value(int status, char ***env);
void	exec_builtin(t_command command, char ***env);
//Pipex
int		pipex(t_command command, char ***env, int infd, int last_command);
//Clean
void	clean_line(t_line *line);
void	clean_command(t_command command);
void	clean_env(char **env);
void	clean_all(t_line *line, char **env);
//Signals
void	sig_handler(int sig);

#endif