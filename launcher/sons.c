/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sons.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:19:05 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/08 18:17:52 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_cmd(t_command command, t_minishell *mini)
{
	if (command.filename && access(command.filename, F_OK) == 0)
	{
		if (access(command.filename, X_OK) == 0)
		{
			execve(command.filename, command.argv, mini->env);
		}
		else
		{
			ft_printf_2("minishell: %s: Permission denied\n", command.argv[0]);
			clean_command(command);
			exit(NO_EXEC_PERMISSION);
		}
	}
	else
	{
		ft_printf_2("minishell: %s: command not found\n", command.argv[0]);
		clean_command(command);
		exit(CMD_NOT_FOUND);
	}
	clean_command(command);
	exit(EXIT_FAILURE);
}

void	first_last_son(t_line *line, t_minishell *mini)
{
	if (line->cmd_index != 0)
		line->cmd_index++;
	ft_fork_protected(&(line->commands[line->cmd_index].pid), mini);
	if (line->commands[line->cmd_index].pid)
		return ;
	son_redirects(line, line->cmd_index, mini);
	exec_builtin(line->commands[line->cmd_index], mini, true);
	ft_exec_cmd(line->commands[line->cmd_index], mini);
}

void	parent_reasign_close_fds(t_line *line)
{
	close(line->pipefd[READ]);
	close(line->pipefd2[WRITE]);
	line->pipefd[READ] = line->pipefd2[READ];
}

void	middle_son(t_line *line, t_minishell *mini)
{
	line->cmd_index++;
	ft_pipe_protected(line->pipefd2, mini);
	ft_fork_protected(&(line->commands[line->cmd_index].pid), mini);
	if (!line->commands[line->cmd_index].pid)
	{
		close(line->pipefd2[READ]);
		line->pipefd[WRITE] = line->pipefd2[WRITE];
		son_redirects(line, line->cmd_index, mini);
		exec_builtin(line->commands[line->cmd_index], mini, true);
		ft_exec_cmd(line->commands[line->cmd_index], mini);
	}
	else
		parent_reasign_close_fds(line);
}
