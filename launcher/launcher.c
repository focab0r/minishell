/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/09 16:38:01 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_exit_value(int status, t_minishell *minishell)
{
	minishell->exit_value = status;
}

bool	is_builtin(char *str)
{
	if (!str)
		return (true);
	else if (ft_strncmp(str, "echo", 5) == 0)
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

void	builtin_save_exit_code(t_command cmd, t_minishell *mini
								, size_t exit_code, bool son)
{
	if (son)
	{
		clean_command(cmd);
		exit(exit_code);
	}
	else
		save_exit_value((int)exit_code, mini);
}

void	exec_builtin(t_command cmd, t_minishell *mini, bool son)
{
	size_t	exit_code;

	if (!cmd.filename && !cmd.argv)
		exit_code = 0;
	else if (ft_strncmp(cmd.argv[0], "cd", 3) == 0)
		exit_code = builtin_cd(cmd, mini);
	else if (ft_strncmp(cmd.argv[0], "echo", 5) == 0)
		exit_code = builtin_echo(cmd);
	else if (ft_strncmp(cmd.argv[0], "pwd", 4) == 0)
		exit_code = builtin_pwd();
	else if (ft_strncmp(cmd.argv[0], "env", 4) == 0)
		exit_code = builtin_env(mini->env);
	else if (ft_strncmp(cmd.argv[0], "export", 7) == 0)
		exit_code = builtin_export(mini, cmd);
	else if (ft_strncmp(cmd.argv[0], "unset", 6) == 0)
		exit_code = builtin_unset(mini, cmd);
	else if (ft_strncmp(cmd.argv[0], "exit", 5) == 0)
		exit_code = builtin_exit(mini, cmd);
	if (is_builtin(cmd.filename))
		builtin_save_exit_code(cmd, mini, exit_code, son);
}
