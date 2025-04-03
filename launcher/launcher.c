/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/02 22:16:09 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_exit_value(int status, t_minishell *minishell)
{
	minishell->exit_value = status;
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

void	exec_builtin(t_command cmd, t_minishell *mini, bool son)		//	necesito line en vez de command para exit
{
	size_t	exit_code;

	if (strncmp(cmd.argv[0], "cd", 3) == 0)
		exit_code = builtin_cd(cmd);
	else if (strncmp(cmd.argv[0], "echo", 5) == 0)
		exit_code = builtin_echo(cmd);
	else if (strncmp(cmd.argv[0], "pwd", 4) == 0)
		exit_code = builtin_pwd();
	else if (strncmp(cmd.argv[0], "env", 4) == 0)
		exit_code = builtin_env(mini->env);
	else if (strncmp(cmd.argv[0], "export", 7) == 0)
		exit_code = builtin_export(mini, cmd);
	else if (strncmp(cmd.argv[0], "unset", 6) == 0)
		exit_code = builtin_unset(mini, cmd);
	else if (strncmp(cmd.argv[0], "exit", 5) == 0)
		exit_code = builtin_exit(mini, cmd);
	if (is_builtin(cmd.filename))
	{
		if (son)
			exit(exit_code);
		else
			save_exit_value((int)exit_code, mini);
	}
}

// int	exec_command(t_line *line, t_minishell *minishell, int *i, int infd)
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
// 		builtin_export(minishell, line->commands[*i]);
// 		close(STDIN_FILENO);
// 	}
// 	else if (ft_strncmp(line->commands[*i].argv[0], "unset", 6) == 0)
// 	{
// 		builtin_unset(minishell, line->commands[*i]);
// 		close(STDIN_FILENO);
// 	}
// 	else if (ft_strncmp(line->commands[*i].argv[0], "exit", 5) == 0)
// 		clean_all(line,  minishell->env);
// 	else if (*i == line->ncommands - 1)
// 		pid = pipex(line->commands[*i], minishell, infd, 1);
// 	else
// 		pid = pipex(line->commands[*i], minishell, infd, 0);
// 	return ((*i)++, pid);
// }

// void	execute_commands(t_line *line, t_minishell *minishell)
// {
// 	int		infd;
// 	int		i;
// 	int		*waitpid_list;
// 	int		status;

// 	infd = dup(STDIN_FILENO);
// 	waitpid_list = (int *) calloc (line->ncommands, sizeof(int));
// 	i = 0;
// 	while (i < line->ncommands)
// 		waitpid_list[i] = exec_command(line, minishell, &i, infd);
// 	i = 0;
// 	while (i < line->ncommands)
// 	{
// 		if (waitpid_list[i])
// 		{
// 			waitpid(waitpid_list[i], &status, 0);
// 			save_exit_value(WEXITSTATUS(status), minishell);
// 		}
// 		else
// 			save_exit_value(0, minishell);
// 		i++;
// 	}
// 	free(waitpid_list);
// 	dup2(infd, STDIN_FILENO);
// 	close(infd);
