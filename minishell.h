/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/08 17:59:25 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <linux/limits.h>
# include <errno.h>

# define WRITE 1
# define READ 0
# define NO_EXEC_PERMISSION 126
# define CMD_NOT_FOUND 127

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

typedef struct s_minishell
{
	t_line	*line;
	char	**env;
	int		exit_value;
} t_minishell;

extern int	g_signal;

//Parser
int		parse_input(t_line **line, char *input, t_minishell *minishell);
void	print_line(t_line *line);
void	pass_till_comma(char *input, int *i);
int		is_special_char(char c);
void	scape_spaces(char *input, int *i);
char	*parse_word(char *input, int *i, t_minishell *minishell);
//	Commands
void	add_argument_at_end(t_command *command, char *word);
void	init_command(t_command *l);
void	add_command_at_end(t_line *line, t_command *command);
//	Vars
char	*replace_vars(char *word, t_minishell *minishell);
char	*check_env(char *word, t_minishell *minishell, int *env_num);
char	*get_env_header(char *env_var);
//	Quotes
char	*escape_quotes(char *str);
//	Alias
char	*expand_alias(char *cmd, t_minishell *minishell);
char	*ft_cmd_in_path(char **div_path, char *cmd, t_minishell *minishell);
char	**get_path(t_minishell *minishell);
char	*ft_strdup_protected(char *str, t_minishell *minishell);
char	*ft_strjoin_protected(char *str1, char *str2, t_minishell *minishell);

//Builtins
bool	is_builtin(char *str);
size_t	builtin_echo(t_command command);
size_t	builtin_cd(t_command command, t_minishell *minishell);
size_t	builtin_pwd(void);
size_t	builtin_env(char **env);
size_t	builtin_export(t_minishell *minishell, t_command command);
size_t	builtin_unset(t_minishell *minishell, t_command command);
//	builtins3
size_t	builtin_exit(t_minishell *mini, t_command cmd);
void	update_pwds(t_minishell *mini);

//Launcher
//	Launcher
void	exec_builtin(t_command command, t_minishell *minishell, bool son);
void	save_exit_value(int status, t_minishell *minishell);
//	Pipex
void	execute_commands(t_line *line, t_minishell *mini);
void	ft_waiting_for_my_sons(t_line *line, t_minishell *mini);
//	Sons
void	ft_exec_cmd(t_command command, t_minishell *mini);
void	first_last_son(t_line *line, t_minishell *mini);
void	parent_reasign_close_fds(t_line *line);
void	middle_son(t_line *line, t_minishell *mini);
//	Redirects
void	pipex_manage_input_heredoc(char *heredoc_lim, t_minishell *mini);
void	pipex_manage_input_redirect(t_command command, t_minishell *mini);
void	pipex_manage_output_redirect(t_command command, t_minishell *mini);
void	son_redirects(t_line *line, size_t cmd_index, t_minishell *mini);
//	Protected
void	ft_fork_protected(pid_t *pid, t_minishell *mini);
void	ft_pipe_protected(int *pipefd, t_minishell *mini);
void	ft_dup2_protected(int fd1, int fd2, t_minishell *mini);

//Clean
void	clean_line(t_line *line);
void	clean_command(t_command command);
void	clean_env(char **env);
void	clean_all(t_minishell *minishell);

//Signals
void	sig_handler(int sig);

#endif