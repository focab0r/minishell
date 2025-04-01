/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/01 21:17:36 by ssousmat         ###   ########.fr       */
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

bool	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (true);
	return (false);
}

void	exec_builtin(t_command command, char ***env, bool son)		//	necesito line en vez de command para exit
{
	size_t	exit_code;

	if (strncmp(command.argv[0], "cd", 3) == 0)
		exit_code = builtin_cd(command);
	else if (strncmp(command.argv[0], "echo", 5) == 0)
		exit_code = builtin_echo(command);
	else if (strncmp(command.argv[0], "pwd", 4) == 0)
		exit_code = builtin_pwd();
	else if (strncmp(command.argv[0], "env", 4) == 0)
		exit_code = builtin_env(*env);
	else if (strncmp(command.argv[0], "export", 7) == 0)
		exit_code = builtin_export(env, command);
	else if (strncmp(command.argv[0], "unset", 6) == 0)
		exit_code = builtin_unset(env, command);
	else if (strncmp(command.argv[0], "exit", 5) == 0)
		exit(0);
	if (is_builtin(command.filename) && son)
		exit(exit_code);
	else
		save_exit_value((int)exit_code, env);
}

// int	exec_command(t_line *line, char ***env, int *i, int infd)
// {
// 	int	pid;

// 	pid = 0;
// 	if (line->commands[*i].argv == NULL)
// 		return ((*i)++, 0);
// 	if (ft_strncmp(line->commands[*i].argv[0], "cd", 3) == 0)
// 	{
// 		builtin_cd(line->commands[*i]);
// 		close(STDIN_FILENO);
// 	}
// 	else if (ft_strncmp(line->commands[*i].argv[0], "export", 7) == 0)
// 	{
// 		builtin_export(env, line->commands[*i]);
// 		close(STDIN_FILENO);
// 	}
// 	else if (ft_strncmp(line->commands[*i].argv[0], "unset", 6) == 0)
// 	{
// 		builtin_unset(env, line->commands[*i]);
// 		close(STDIN_FILENO);
// 	}
// 	else if (ft_strncmp(line->commands[*i].argv[0], "exit", 5) == 0)
// 		clean_all(line, *env);
// 	else
// 		pipex(line, env);
// 	return ((*i)++, pid);
// }

// void	execute_commands(t_line *line, char ***env)
// {
// 	int		infd;
// 	int		i;
// 	int		*waitpid_list;
// 	int		status;

// 	infd = dup(STDIN_FILENO);
// 	waitpid_list = (int *) calloc (line->ncommands, sizeof(int));
// 	i = 0;
// 	while (i < line->ncommands)
// 		waitpid_list[i] = exec_command(line, env, &i, infd);
// 	i = 0;
// 	while (i < line->ncommands)
// 	{
// 		if (waitpid_list[i])
// 		{
// 			waitpid(waitpid_list[i], &status, 0);
// 			save_exit_value(WEXITSTATUS(status), env);
// 		}
// 		else
// 			save_exit_value(0, env);
// 		i++;
// 	}
// 	free(waitpid_list);
// 	dup2(infd, STDIN_FILENO);
// 	close(infd);
// }
