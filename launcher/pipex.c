/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:53:12 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/08 21:33:34 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_waiting_for_my_sons(t_line *line, t_minishell *mini)
{
	pid_t	wpid;
	int		status;
	
	wpid = wait(&status);
	while (wpid > 0)
	{
		printf("--%d--\n", line->commands[line->cmd_index].pid);
		if (wpid == line->commands[line->cmd_index].pid)
		{
			if (WIFEXITED(status))
				save_exit_value(WEXITSTATUS(status), mini);
			else if (WIFSIGNALED(status))
				save_exit_value(128 + WTERMSIG(status), mini);
			else
				save_exit_value(1, mini);
		}
		wpid = wait(&status);
	}
}

void	execute_commands(t_line *line, t_minishell *mini)
{
	line->cmd_index = 0;
	ft_pipe_protected(line->pipefd, mini);
	if (is_builtin(line->commands[line->cmd_index].filename) && line->ncommands == 1)
		exec_builtin(line->commands[0], mini, false);
	else
		first_last_son(line, mini);
	close(line->pipefd[WRITE]);
	while (line->cmd_index + 2 < (size_t)line->ncommands)
		middle_son(line, mini);
	if (line->ncommands >= 2)
	{
		line->cmd_index++;
		first_last_son(line, mini);
	}
	close(line->pipefd[READ]);
	ft_waiting_for_my_sons(line, mini);
}
