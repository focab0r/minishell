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

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_command
{
	char				*filename;
	int					argc;
	char				**argv;
} t_command;

typedef t_command *c_list;

typedef struct s_line
{
	int			ncommands;
	t_command	*commands ;
	char		*redirect_input;
	char		*redirect_output;
	char		*redirect_error;
	int			background;
} t_line;

typedef struct s_minishell
{
    char 				*PATH;
	c_list				commands;
} t_minishell;

//Commands
void add_argument_at_end(c_list *l, char *argv);
void init_command(c_list *l);
void add_command_at_end(t_line *line, c_list list);
void print_line(t_line *line);
//Parser
void parse_input(t_line *line, char *input);
//Quotes
void	escape_quotes(t_line *line);
//Alias
void expand_alias(t_minishell m, t_line *line);
//vars
void replace_vars(t_minishell m, t_line *line);
//Execute
void execute_commands(t_line *line);
//Signals
void sig_handler(int sig, siginfo_t *info, void *context);

#endif