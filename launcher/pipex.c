/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:53:12 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/01 21:16:59 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_waiting_for_my_sons(t_line *line, char ***env)
{
	pid_t	wpid;
	int		status;
	
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == line->commands[line->cmd_index].pid)
		{
			if (WIFEXITED(status))
				save_exit_value(WEXITSTATUS(status), env);
			else if (WIFSIGNALED(status))
				save_exit_value(128 + WTERMSIG(status), env);
			else
				save_exit_value(1, env);
		}
		wpid = wait(&status);
	}
}

void	execute_commands(t_line *line, char ***env)
{
	line->cmd_index = 0;
	ft_pipe_protected(line->pipefd, line);
	if (is_builtin(line->commands[line->cmd_index].filename) && line->ncommands == 1)
		exec_builtin(line->commands[0], env, false);
	else
		first_last_son(line, env);
	close(line->pipefd[WRITE]);
	while (line->cmd_index + 1 < (size_t)line->ncommands)
		middle_son(line, env);
	if (line->ncommands >= 2)
		first_last_son(line, env);
	close(line->pipefd[READ]);
	ft_waiting_for_my_sons(line, env);
}
