/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:38:39 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/03 14:06:31 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipex_manage_input_heredoc(char *heredoc_lim, t_minishell *mini)
{
	int		heredocfd[2];
	char	*here_doc_line;

	ft_pipe_protected(heredocfd, mini);
	while (1)
	{
		ft_printf_2("> ");
		here_doc_line = get_next_line(STDIN_FILENO);
		if (!here_doc_line)
			break ;
		if (!ft_strncmp(here_doc_line, heredoc_lim, ft_strlen(heredoc_lim)) \
			&& here_doc_line[ft_strlen(heredoc_lim)] == '\n')
		{
			free(here_doc_line);
			break ;
		}
		write(heredocfd[WRITE], here_doc_line, ft_strlen(here_doc_line));
		free(here_doc_line);
	}
	close(heredocfd[WRITE]);
	ft_dup2_protected(heredocfd[READ], STDIN_FILENO, mini);
	close(heredocfd[READ]);
}

void	pipex_manage_input_redirect(t_command command, t_minishell *mini)
{
	int	aux_fd;

	aux_fd = open(command.redirect_input, O_RDONLY);
	if (aux_fd < 0)
	{
		ft_printf_2("minishell: %s: No such file or directory\n", command.redirect_input);
		exit(EXIT_FAILURE);
	}
	ft_dup2_protected(aux_fd, STDIN_FILENO, mini);
	close(aux_fd);
}

void	pipex_manage_output_redirect(t_command command, t_minishell *mini)
{
	int	aux_fd;

	if (command.redirect_output && !command.append_output)
		aux_fd = open(command.redirect_output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		aux_fd = open(command.append_output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (aux_fd < 0)
	{
		if (command.redirect_output && !command.append_output)
			ft_printf_2("minishell: %s: No such file or directory\n", command.redirect_output);
		else
			ft_printf_2("minishell: %s: No such file or directory\n", command.append_output);
		exit(EXIT_FAILURE);
	}
	ft_dup2_protected(aux_fd, STDOUT_FILENO, mini);
	close(aux_fd);
}

void	son_redirects(t_line *line, size_t cmd_index, t_minishell *mini)
{
	signal(SIGQUIT, SIG_DFL);
	if (line->commands[cmd_index].append_input)
		pipex_manage_input_heredoc(line->commands[cmd_index].append_input, mini);
	else if (line->commands[cmd_index].redirect_input)
		pipex_manage_input_redirect(line->commands[cmd_index], mini);
	else if (cmd_index > 0)
	{
		ft_dup2_protected(line->pipefd[READ], STDIN_FILENO, mini);
	}
	close(line->pipefd[READ]);
	if (line->commands[cmd_index].redirect_output || line->commands[cmd_index].append_output)
		pipex_manage_output_redirect(line->commands[cmd_index], mini);
	else if (cmd_index + 1 < line->ncommands)
	{
		ft_dup2_protected(line->pipefd[WRITE], STDOUT_FILENO, mini);
	}
	close(line->pipefd[WRITE]);
}
