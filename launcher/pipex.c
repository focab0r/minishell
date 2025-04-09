/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:53:12 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/09 14:26:29 by ssousmat         ###   ########.fr       */
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

// void print_line(t_line *line)
// {
// 	ft_printf("--------------------------------\n");	//comentar
// 	ft_printf("Nº commands: %d\n", line->ncommands);
// 	int i = 0;
// 	int e;
// 	while (i < line->ncommands)
// 	{
// 		t_command c = (line->commands)[i];
// 		ft_printf("<<<<< %d >>>>>\n", i);
// 		ft_printf("--> Command name: %s\n", c.filename);
// 		ft_printf("--> Nº Argc: %d\n", c.argc);
// 		e = 0;
// 		while (e < c.argc)
// 		{
// 			ft_printf("----> Arg: %s\n", (c.argv)[e]);
// 			e++;
// 		}
// 		if (c.redirect_output != NULL)
// 			ft_printf("--> Output redirected to: %s\n", c.redirect_output);
// 		if (c.redirect_input != NULL)
// 			ft_printf("--> Input redirected to: %s\n", c.redirect_input);
// 		if (c.append_output != NULL)
// 			ft_printf("--> Output appended to: %s\n", c.append_output);
// 		if (c.append_input != NULL)
// 			ft_printf("--> Input appended to: %s\n", c.append_input);
// 		i++;
// 	}
// 	ft_printf("--------------------------------\n");
// }

void	execute_commands(t_line *line, t_minishell *mini)
{
	line->cmd_index = 0;
//	print_line(line);		//quitar
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
