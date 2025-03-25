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

void	save_exit_value(int status, char ***env)
{
	t_command	*command;
	char		*status_str;

	command = (t_command *) malloc (1 * sizeof(t_command));
	command->argc = 2;
	command->argv = (char **) malloc (2 * sizeof(char *));
	status_str = ft_itoa(status);
	command->argv[1] = (char *) malloc (ft_strlen(status_str) + 3);
	command->argv[1][0] = '?';
	command->argv[1][1] = '=';
	ft_strlcpy(&(command->argv[1][2]), status_str, ft_strlen(status_str)+1);
	free(status_str);
	builtin_export(env, *command);
	free(command->argv[1]);
	free(command->argv);
	free(command);
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

void	exec_builtin(t_command command, char ***env)		//	necesito line en vez de command o line->ncommands para exit
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
			builtin_env(*env);
		else if (strncmp(command.argv[0], "export", 7) == 0)
			builtin_export(env, command);
		else if (strncmp(command.argv[0], "exit", 5) == 0)
			exit(0);
	}
}

int	exec_command(t_line *line, char ***env, int *i, int infd)
{
	int	pid;

	pid = 0;
	if (ft_strncmp(line->commands[*i].argv[0], "cd", 3) == 0)
	{
		builtin_cd(line->commands[*i]);
		close(STDIN_FILENO);
	}
	else if (ft_strncmp(line->commands[*i].argv[0], "export", 7) == 0)
	{
		builtin_export(env, line->commands[*i]);
		close(STDIN_FILENO);
	}
	else if (ft_strncmp(line->commands[*i].argv[0], "unset", 6) == 0)
	{
		builtin_unset(env, line->commands[*i]);
		close(STDIN_FILENO);
	}
	else if (ft_strncmp(line->commands[*i].argv[0], "exit", 5) == 0)
		clean_all(line, *env);
	else if (*i == line->ncommands - 1)
		pid = pipex(line->commands[*i], env, infd, 1);
	else
		pid = pipex(line->commands[*i], env, infd, 0);
	return ((*i)++, pid);
}

void	execute_commands(t_line *line, char ***env)
{
	int		infd;
	int		i;
	int		*waitpid_list;
	int		status;

	infd = dup(STDIN_FILENO);
	waitpid_list = (int *) calloc (line->ncommands, sizeof(int));
	i = 0;
	while (i < line->ncommands)
		waitpid_list[i] = exec_command(line, env, &i, infd);
	i = 0;
	while (i < line->ncommands)
	{
		if (waitpid_list[i])
		{
			waitpid(waitpid_list[i], &status, 0);
			save_exit_value(WEXITSTATUS(status), env);
		}
		else
			save_exit_value(0, env);
		i++;
	}
	free(waitpid_list);
	dup2(infd, STDIN_FILENO);
	close(infd);
}
