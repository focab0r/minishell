/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/03/25 19:50:26 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_exit_value(int status, t_minishell *minishell)
{
	minishell->exit_value = status;
}

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_command command, t_minishell *minishell)		//	necesito line en vez de command o line->ncommands para exit
{
	if (!is_builtin(command.argv[0]))
	{
		write(2, "Error: Command not found\n", 25);
		exit(127);
	}
	else
	{
		if (strncmp(command.argv[0], "cd", 3) == 0)
			builtin_cd(command);
		else if (strncmp(command.argv[0], "echo", 5) == 0)
			builtin_echo(command);
		else if (strncmp(command.argv[0], "pwd", 4) == 0)
			builtin_pwd();
		else if (strncmp(command.argv[0], "env", 4) == 0)
			builtin_env(minishell->env);
		else if (strncmp(command.argv[0], "export", 7) == 0)
			builtin_export(minishell, command);
		else if (strncmp(command.argv[0], "exit", 5) == 0)
			exit(0);
	}
}

int	exec_command(t_line *line, t_minishell *minishell, int *i, int infd)
{
	int	pid;

	pid = 0;
	if (line->commands[*i].argv == NULL)
		return ((*i)++, 0);
	if (ft_strncmp(line->commands[*i].argv[0], "cd", 3) == 0)
	{
		builtin_cd(line->commands[*i]);
		close(STDIN_FILENO);
	}
	else if (ft_strncmp(line->commands[*i].argv[0], "export", 7) == 0)
	{
		builtin_export(minishell, line->commands[*i]);
		close(STDIN_FILENO);
	}
	else if (ft_strncmp(line->commands[*i].argv[0], "unset", 6) == 0)
	{
		builtin_unset(minishell, line->commands[*i]);
		close(STDIN_FILENO);
	}
	else if (ft_strncmp(line->commands[*i].argv[0], "exit", 5) == 0)
		clean_all(line,  minishell->env);
	else if (*i == line->ncommands - 1)
		pid = pipex(line->commands[*i], minishell, infd, 1);
	else
		pid = pipex(line->commands[*i], minishell, infd, 0);
	return ((*i)++, pid);
}

void	execute_commands(t_line *line, t_minishell *minishell)
{
	int		infd;
	int		i;
	int		*waitpid_list;
	int		status;

	infd = dup(STDIN_FILENO);
	waitpid_list = (int *) calloc (line->ncommands, sizeof(int));
	i = 0;
	while (i < line->ncommands)
		waitpid_list[i] = exec_command(line, minishell, &i, infd);
	i = 0;
	while (i < line->ncommands)
	{
		if (waitpid_list[i])
		{
			waitpid(waitpid_list[i], &status, 0);
			save_exit_value(WEXITSTATUS(status), minishell);
		}
		else
			save_exit_value(0, minishell);
		i++;
	}
	free(waitpid_list);
	dup2(infd, STDIN_FILENO);
	close(infd);
}
