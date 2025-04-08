/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:12:55 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/08 16:51:10 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	builtin_exit(t_minishell *mini, t_command cmd)
{
	if (mini->line->ncommands == 1)
		ft_printf_2("exit\n");
	if (cmd.argc > 1)
	{
		if (!ft_isnum(cmd.argv[1]))
		{
			ft_printf_2("minishell: exit: %s: numeric argument required\n", \
						cmd.argv[1]);
			exit(2);
		}
		else if (cmd.argc > 2)
		{
			ft_printf_2("minishell: exit: too many arguments\n");
			if (mini->line->ncommands == 1)
				return (1);
			exit(1);
		}
		exit(ft_atoi((const char*)cmd.argv[1]));
	}
	else
		exit(0);
}

void	update_env_var(char *name, char *value, t_minishell *mini)
{
	int		index;
	char	*temp;
	char	*updated;

	temp = ft_strjoin(name, "=");
	updated = ft_strjoin(temp, value);
	free(temp);
	temp = check_env(name, mini, &index);
	if (temp)
	{
		free(temp);
		free(mini->env[index]);
		mini->env[index] = updated;
	}
}

void	manual_unset(t_minishell *mini, char *str)
{
	t_command *command;
	
	command = (t_command *) malloc (1*sizeof(t_command));
	command->argc = 2;
	command->argv = (char **) malloc (2*sizeof(char *));
	command->filename = ft_strdup("unset");
	command->argv[0] = ft_strdup("unset");
	command->argv[1] = str;
	builtin_unset(mini, *command);
	free(command->argv[0]);
	free(command->argv);
	free(command);
}

void	update_pwds(t_minishell *mini)
{
	char	*oldpwd;
	char	*oldoldpwd;
	char	pwd[PATH_MAX];

	oldpwd = check_env("PWD", mini, NULL);
	if (oldpwd)
	{
		update_env_var("OLDPWD", oldpwd, mini);
		free(oldpwd);
	}
	else
	{
		oldoldpwd = check_env("OLDPWD", mini, NULL);
		if (oldoldpwd)
		{
			free(oldoldpwd);
			manual_unset(mini, "OLDPWD");
		}
	}
	if (getcwd(pwd, sizeof(pwd)))
		update_env_var("PWD", pwd, mini);
}
